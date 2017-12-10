#pragma once

#include <sam3x8e.h>

////
//
//  Port manipulation for SAM3X procesors.
//
//      See section 31 in:
//
//          http://www.atmel.com/Images/Atmel-11057-32-bit-Cortex-M3-Microcontroller-SAM3X-SAM3A_Datasheet.pdf.
//
////

typedef uint32_t word_t;                            // port word type

enum port_enum_t { P_, PA, PB, PC, PD, PE, PF };

template<port_enum_t PORT> struct port_t
{
    static inline volatile word_t& puer();          // pull-up enable
    static inline volatile word_t& pder();          // pull-up disable
    static inline const volatile word_t& pusr();    // pull-up status
    static inline volatile word_t& oer();           // output drive enable
    static inline volatile word_t& odr();           // output drive disable
    static inline const volatile word_t& osr();     // output drive status
    static inline volatile word_t& mder();          // multi-drive enable
    static inline volatile word_t& mddr();          // multi-drive disable
    static inline const volatile word_t& mdsr();    // multi-drive status
    static inline volatile word_t& sodr();          // set output register
    static inline volatile word_t& codr();          // clear output register
    static inline volatile word_t& odsr();          // output data status (writeable)
    static inline volatile word_t& ower();          // output write enable
    static inline volatile word_t& owdr();          // output write disable
    static inline const volatile word_t& owsr();    // output write status
    static inline const volatile word_t& pdsr();    // data input register
};

template<> struct port_t<PA>
{
    static const port_enum_t port = PA;

    static inline volatile word_t& puer()       { return REG_PIOA_PUER; }
    static inline volatile word_t& pudr()       { return REG_PIOA_PUDR; }
    static inline const volatile word_t& pusr() { return REG_PIOA_PUSR; }
    static inline volatile word_t& oer()        { return REG_PIOA_OER; }
    static inline volatile word_t& odr()        { return REG_PIOA_ODR; }
    static inline const volatile word_t& osr()  { return REG_PIOA_OSR; }
    static inline volatile word_t& mder()       { return REG_PIOA_MDER; }
    static inline volatile word_t& mddr()       { return REG_PIOA_MDDR; }
    static inline const volatile word_t& mdsr() { return REG_PIOA_MDSR; }
    static inline volatile word_t& sodr()       { return REG_PIOA_SODR; }
    static inline volatile word_t& codr()       { return REG_PIOA_CODR; }
    static inline volatile word_t& odsr()       { return REG_PIOA_ODSR; }
    static inline volatile word_t& ower()       { return REG_PIOA_OWER; }
    static inline volatile word_t& owdr()       { return REG_PIOA_OWDR; }
    static inline const volatile word_t& owsr() { return REG_PIOA_OWSR; }
    static inline const volatile word_t& pdsr() { return REG_PIOA_PDSR; }
};

template<> struct port_t<PB>
{
    static const port_enum_t port = PB;

    static inline volatile word_t& puer()       { return REG_PIOB_PUER; }
    static inline volatile word_t& pudr()       { return REG_PIOB_PUDR; }
    static inline const volatile word_t& pusr() { return REG_PIOB_PUSR; }
    static inline volatile word_t& oer()        { return REG_PIOB_OER; }
    static inline volatile word_t& odr()        { return REG_PIOB_ODR; }
    static inline const volatile word_t& osr()  { return REG_PIOB_OSR; }
    static inline volatile word_t& mder()       { return REG_PIOB_MDER; }
    static inline volatile word_t& mddr()       { return REG_PIOB_MDDR; }
    static inline const volatile word_t& mdsr() { return REG_PIOB_MDSR; }
    static inline volatile word_t& sodr()       { return REG_PIOB_SODR; }
    static inline volatile word_t& codr()       { return REG_PIOB_CODR; }
    static inline volatile word_t& odsr()       { return REG_PIOB_ODSR; }
    static inline volatile word_t& ower()       { return REG_PIOB_OWER; }
    static inline volatile word_t& owdr()       { return REG_PIOB_OWDR; }
    static inline const volatile word_t& owsr() { return REG_PIOB_OWSR; }
    static inline const volatile word_t& pdsr() { return REG_PIOB_PDSR; }
};

template<> struct port_t<PC>
{
    static const port_enum_t port = PC;

    static inline volatile word_t& puer()       { return REG_PIOC_PUER; }
    static inline volatile word_t& pudr()       { return REG_PIOC_PUDR; }
    static inline const volatile word_t& pusr() { return REG_PIOC_PUSR; }
    static inline volatile word_t& oer()        { return REG_PIOC_OER; }
    static inline volatile word_t& odr()        { return REG_PIOC_ODR; }
    static inline const volatile word_t& osr()  { return REG_PIOC_OSR; }
    static inline volatile word_t& mder()       { return REG_PIOC_MDER; }
    static inline volatile word_t& mddr()       { return REG_PIOC_MDDR; }
    static inline const volatile word_t& mdsr() { return REG_PIOC_MDSR; }
    static inline volatile word_t& sodr()       { return REG_PIOC_SODR; }
    static inline volatile word_t& codr()       { return REG_PIOC_CODR; }
    static inline volatile word_t& odsr()       { return REG_PIOC_ODSR; }
    static inline volatile word_t& ower()       { return REG_PIOC_OWER; }
    static inline volatile word_t& owdr()       { return REG_PIOC_OWDR; }
    static inline const volatile word_t& owsr() { return REG_PIOC_OWSR; }
    static inline const volatile word_t& pdsr() { return REG_PIOC_PDSR; }
};

template<> struct port_t<PD>
{
    static const port_enum_t port = PD;

    static inline volatile word_t& puer()       { return REG_PIOD_PUER; }
    static inline volatile word_t& pudr()       { return REG_PIOD_PUDR; }
    static inline const volatile word_t& pusr() { return REG_PIOD_PUSR; }
    static inline volatile word_t& oer()        { return REG_PIOD_OER; }
    static inline volatile word_t& odr()        { return REG_PIOD_ODR; }
    static inline const volatile word_t& osr()  { return REG_PIOD_OSR; }
    static inline volatile word_t& mder()       { return REG_PIOD_MDER; }
    static inline volatile word_t& mddr()       { return REG_PIOD_MDDR; }
    static inline const volatile word_t& mdsr() { return REG_PIOD_MDSR; }
    static inline volatile word_t& sodr()       { return REG_PIOD_SODR; }
    static inline volatile word_t& codr()       { return REG_PIOD_CODR; }
    static inline volatile word_t& odsr()       { return REG_PIOD_ODSR; }
    static inline volatile word_t& ower()       { return REG_PIOD_OWER; }
    static inline volatile word_t& owdr()       { return REG_PIOD_OWDR; }
    static inline const volatile word_t& owsr() { return REG_PIOD_OWSR; }
    static inline const volatile word_t& pdsr() { return REG_PIOD_PDSR; }
};

template<port_enum_t PORT, uint8_t BIT> struct pin_t
{
    typedef port_t<PORT> port;
    static_assert(BIT < 8 * sizeof(word_t), "bit out of range");
    static const uint8_t bitpos = BIT;
    static const word_t bitmask = 1<<BIT;
};

enum pullup_t { no_pull, pull_up, pull_down };

template<class PIN> struct input_t
{
    template<pullup_t PULLUP = no_pull>
    static inline void setup()
    {
        static_assert(PULLUP != pull_down, "pulldown not supported on this architecture");
        PIN::port::odr() = PIN::bitmask;
        (PULLUP == pull_up ? PIN::port::puer() : PIN::port::pudr()) = PIN::bitmask;
    }

    static inline bool get() { return (PIN::port::pdir() & PIN::bitmask) != 0; }
};

enum drain_t { common_drain, open_drain };

template<class PIN> struct output_t
{
    template<drain_t DRAIN = common_drain>
    static inline void setup()
    {
        PIN::port::oer() = PIN::bitmask;
        (DRAIN == open_drain ? PIN::port::mder() : PIN::port::mddr()) = PIN::bitmask;
    }

    static inline bool get() { return (PIN::port::pdsr() & PIN::bitmask) != 0; }
    static inline void set(bool x) { x ? set() : clear(); }
    static inline void set() { PIN::port::sodr() = PIN::bitmask; }
    static inline void clear() { PIN::port::codr() = PIN::bitmask; }
    static inline void toggle() { get() ? clear() : set(); }
};

