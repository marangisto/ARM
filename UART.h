#pragma once

// hack around the fact that we use g++, not gcc!
//#undef FDEV_SETUP_STREAM
//#define FDEV_SETUP_STREAM(p, g, f) { 0, 0, f, 0, 0, p, g, 0 }

extern "C" {
uint32_t pmc_enable_periph_clk(uint32_t ul_id);
uint32_t pmc_disable_periph_clk(uint32_t ul_id);
}

template<uint32_t BUFFER_SIZE>
struct circular_buffer_t
{
    circular_buffer_t()
    {
        init();
    }

    void init()
    {
        m_head = m_tail = 0;
    }

    void store_char(uint8_t c)
    {
        int i = (uint32_t) (m_head + 1) % BUFFER_SIZE;

        if (i != m_tail)
        {
            m_buf[m_head] = c;
            m_head = i;
        }
    }
 
    volatile uint8_t m_buf[BUFFER_SIZE];
    volatile int m_head, m_tail;
};

class uart_t
{
public:
    template<uint32_t baudRate>
    static void setup()
    {
        uint32_t modeReg = UART_MR_CHMODE_NORMAL | (static_cast<uint32_t>(US_MR_CHRL_8_BIT | US_MR_NBSTOP_1_BIT | UART_MR_PAR_NO) & 0x00000E00);
        // FOR USART, also do: modeReg |= US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHMODE_NORMAL;
        Uart *pUart = UART;
        IRQn_Type dwIrq = UART_IRQn;

        pmc_enable_periph_clk(ID_UART); // FIXME: template

        pUart->UART_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;
        pUart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS;
        pUart->UART_MR = modeReg;
        pUart->UART_BRGR = (SystemCoreClock / baudRate) >> 4;
        pUart->UART_IDR = 0xFFFFFFFF;
        pUart->UART_IER = UART_IER_RXRDY | UART_IER_OVRE | UART_IER_FRAME;
        NVIC_EnableIRQ(dwIrq);

        m_rx_buf.init();
        m_tx_buf.init();

        pUart->UART_CR = UART_CR_RXEN | UART_CR_TXEN;

        //stdin = &input;
        //stdout = &output;
    }

    static void stop(void)
    {
        IRQn_Type dwIrq = UART_IRQn;

        m_rx_buf.m_head = m_rx_buf.m_tail;
        flush();
        NVIC_DisableIRQ(dwIrq);
        pmc_disable_periph_clk(ID_UART);    // FIXME: template
    }

    static int getChar()
    {
        //loop_until_bit_is_set(UCSR0A, RXC0);
        //return static_cast<uint8_t>(UDR0);
        return 0;
    }

    static void put_char(uint8_t c)
    {
        Uart *pUart = UART;

        if (((pUart->UART_SR & UART_SR_TXRDY) != UART_SR_TXRDY) | (m_tx_buf.m_tail != m_tx_buf.m_head))
        {
            int nextWrite = (m_tx_buf.m_head + 1) % buffer_size;
            while (m_tx_buf.m_tail == nextWrite)
                /* block until we have buffer space */;
            m_tx_buf.m_buf[m_tx_buf.m_head] = c;
            m_tx_buf.m_head = nextWrite;
            pUart->UART_IER = UART_IER_TXRDY;   // tx-interrupt enable
        }
        else 
            pUart->UART_THR = c;
    }

    static int get_char(void)
    {
        if (m_rx_buf.m_head == m_rx_buf.m_tail)
            return -1;

        uint8_t c = m_rx_buf.m_buf[m_rx_buf.m_tail];

        m_rx_buf.m_tail = (unsigned int) (m_rx_buf.m_tail + 1) % buffer_size;
        return c;
    }

    static int peek(void)
    {
        return m_rx_buf.m_head == m_rx_buf.m_tail ? -1 : m_rx_buf.m_buf[m_rx_buf.m_tail];
    }

    static void flush(void)
    {
        Uart *pUart = UART;

        while (m_tx_buf.m_head != m_tx_buf.m_tail)
            /* more characters */; 
        while ((pUart->UART_SR & UART_SR_TXEMPTY) != UART_SR_TXEMPTY)
            /* complete transmission */ ;
    }

    static void irq_handler( void )
    {
        Uart *pUart = UART;
        uint32_t status = pUart->UART_SR;

        if ((status & UART_SR_RXRDY) == UART_SR_RXRDY)
            m_rx_buf.store_char(pUart->UART_RHR);

        if ((status & UART_SR_TXRDY) == UART_SR_TXRDY) 
        {
            if (m_tx_buf.m_tail != m_tx_buf.m_head) {
                pUart->UART_THR = m_tx_buf.m_buf[m_tx_buf.m_tail];
                m_tx_buf.m_tail = (unsigned int)(m_tx_buf.m_tail + 1) % buffer_size;
            } else
                pUart->UART_IDR = UART_IDR_TXRDY;  // mask transmit interrupt
        }

        if ((status & UART_SR_OVRE) == UART_SR_OVRE || (status & UART_SR_FRAME) == UART_SR_FRAME)
            pUart->UART_CR |= UART_CR_RSTSTA;
    }

private:
    static const uint32_t buffer_size = 128;
    /*
    static int get_char_S(FILE *stream)
    {
        return getChar();
    }

    static int put_char_S(char c, FILE *stream)
    {
        if (c == '\n')
            putChar('\r');
        putChar(c);
        return 0;
    }

    static FILE input;
    static FILE output;
    */
    static circular_buffer_t<buffer_size> m_rx_buf, m_tx_buf;
};

circular_buffer_t<uart_t::buffer_size> uart_t::m_rx_buf;
circular_buffer_t<uart_t::buffer_size> uart_t::m_tx_buf;

void UART_Handler(void)
{
    uart_t::irq_handler();
}

//FILE UART::input = FDEV_SETUP_STREAM(NULL, UART::get_char_S, _FDEV_SETUP_READ);
//FILE UART::output = FDEV_SETUP_STREAM(UART::put_char_S, NULL, _FDEV_SETUP_WRITE);

