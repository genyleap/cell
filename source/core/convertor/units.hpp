/*!
 * @file        convertor.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Unit convertor.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_UNIT_CONVERTOR_HPP
#define CELL_UNIT_CONVERTOR_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("abstracts/convertor.hpp")
#   include "abstracts/convertor.hpp"
#else
#   error "Cell's "abstracts/convertor.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Convertors::Units)

struct UnitItems final
{
    JSonValue items;
};

static const constexpr std::string_view UNITS {"units"};

/**
 * @brief Enumeration of length units.
 */
enum class LengthUnit
{
    Meter,        //!< Meter
    Kilometer,    //!< Kilometer
    Centimeter,   //!< Centimeter
    Millimeter,   //!< Millimeter
    Micrometer,   //!< Micrometer
    Nanometer,    //!< Nanometer
    Mile,         //!< Mile
    Yard,         //!< Yard
    Foot,         //!< Foot
    Inch,         //!< Inch
    LightYear     //!< Light Year
};

/**
 * @brief Class for converting length units.
 */
class Length : public Abstracts::Convertor::UnitConverter<LengthUnit> {
public:
    Length();
    ~Length();
    /**
     * @brief Converts a value from one length unit to another.
     *
     * @param value The value to be converted.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted value.
     */
    double convert(double value, LengthUnit fromUnit, LengthUnit toUnit);

    /**
     * @brief Converts a LengthUnit enum value to its string representation.
     *
     * @param unit The LengthUnit value to convert.
     * @return The string representation of the LengthUnit.
     */
    std::string toString(LengthUnit unit);

private:
    std::array<std::string, 11> m_lengthData;
    static const constexpr std::string_view LENGTH {"length"};
    System::EngineController engineController;
};

/**
 * @brief Enumeration of temperature units.
 */
enum class TemperatureUnit
{
    Celsius,    //!< Celsius
    Fahrenheit, //!< Fahrenheit
    Kelvin      //!< Kelvin
};

/**
 * @brief Class for converting temperature units.
 */
class Temperature : public Abstracts::Convertor::UnitConverter<TemperatureUnit> {
public:
    Temperature();
    ~Temperature();
    /**
     * @brief Converts a temperature value from one unit to another.
     *
     * @param value The value to be converted.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted value.
     */
    double convert(double value, TemperatureUnit fromUnit, TemperatureUnit toUnit);

    /**
     * @brief Converts a TemperatureUnit enum value to its string representation.
     *
     * @param unit The TemperatureUnit value to convert.
     * @return The string representation of the TemperatureUnit.
     */
    std::string toString(TemperatureUnit unit);

private:
    std::array<std::string, 4> m_temperatureData;
    static const constexpr std::string_view TEMPERATURE {"temperature"};
    System::EngineController engineController;
};

/**
 * @brief Enumeration of area units.
 */
enum class AreaUnit
{
    SquareMeter,        //!< Square meter
    SquareKilometer,    //!< Square kilometer
    SquareCentimeter,   //!< Square centimeter
    SquareMillimeter,   //!< Square millimeter
    SquareMicrometer,   //!< Square micrometer
    Hectare,            //!< Hectare
    SquareMile,         //!< Square mile
    SquareYard,         //!< Square yard
    SquareFoot,         //!< Square foot
    SquareInch,         //!< Square inch
    Acre                //!< Acre
};

/**
 * @brief Class for converting area units.
 */
class Area : public Abstracts::Convertor::UnitConverter<AreaUnit> {
public:
    Area();
    ~Area();
    /**
     * @brief Converts an area value from one unit to another.
     *
     * @param value The value to be converted.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted value.
     */
    double convert(double value, AreaUnit fromUnit, AreaUnit toUnit);

    /**
     * @brief Converts an AreaUnit enum value to its string representation.
     *
     * @param unit The AreaUnit value to convert.
     * @return The string representation of the AreaUnit.
     */
    std::string toString(AreaUnit unit);

private:
    std::array<std::string, 11> m_areaData;
    static const constexpr std::string_view AREA {"area"};
    System::EngineController engineController;
};

/**
 * @brief Enumeration of weight units.
 */
enum class WeightUnit
{
    Kilogram,           //!< Kilogram
    Gram,               //!< Gram
    Milligram,          //!< Milligram
    Microgram,          //!< Microgram
    MetricTon,          //!< Metric ton
    LongTon,            //!< Long ton
    ShortTon,           //!< Short ton
    Pound,              //!< Pound
    Ounce,              //!< Ounce
    Carrat,             //!< Carrat
    AtomicMassUnit      //!< Atomic mass unit
};

/**
 * @brief Class for converting weight units.
 */
class Weight : public Abstracts::Convertor::UnitConverter<WeightUnit> {
public:
    Weight();
    ~Weight();

    /**
     * @brief Converts a weight value from one unit to another.
     *
     * @param value The value to be converted.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted value.
     */
    double convert(double value, WeightUnit fromUnit, WeightUnit toUnit);

    /**
     * @brief Converts a WeightUnit enum value to its string representation.
     *
     * @param unit The WeightUnit value to convert.
     * @return The string representation of the WeightUnit.
     */
    std::string toString(WeightUnit unit);

private:
    std::array<std::string, 11> m_weightData;
    static const constexpr std::string_view WEIGHT {"weight"};
    System::EngineController engineController;
};

/**
 * @enum TimeUnit
 * Enumerates the different time units supported by the TimeConverter class.
 */
enum class TimeUnit
{
    Second,         //!< Second
    Millisecond,    //!< Millisecond
    Microsecond,    //!< Microsecond
    Nanosecond,     //!< Nanosecond
    Picosecond,     //!< Picosecond
    Minute,         //!< Minute
    Hour,           //!< Hour
    Day,            //!< Day
    Week,           //!< Week
    Month,          //!< Month
    Year            //!< Year
};

/**
 * @class TimeConverter
 * @brief Converts time values between different units.
 */
class Time : public Abstracts::Convertor::UnitConverter<TimeUnit> {
public:
    Time();
    ~Time();
    /**
     * @brief Converts a time value from one unit to another.
     * @param value The value to be converted.
     * @param fromUnit The unit of the value to convert from.
     * @param toUnit The unit to convert the value to.
     * @return The converted value.
     */
    double convert(double value, TimeUnit fromUnit, TimeUnit toUnit);

    /**
     * @brief Converts a TimeUnit value to its corresponding string representation.
     * @param unit The TimeUnit value to convert.
     * @return The string representation of the TimeUnit value.
     */
    std::string toString(TimeUnit unit);

private:
    std::array<std::string, 11> m_timeData;
    static const constexpr std::string_view TIME {"time"};
    System::EngineController engineController;
};

/**
 * @brief The enumeration representing different speed units.
 */
enum class SpeedUnit
{
    MeterPerSecond,     //!< Meter per second
    KilometerPerHour,   //!< Kilometer per hour
    MilePerHour,        //!< Mile per hour
    FootPerSecond,      //!< Foot per second
    Knot                //!< Knot
};

/**
 * @brief The SpeedConverter class for converting speed values between different units.
 */
class Speed : public Abstracts::Convertor::UnitConverter<SpeedUnit> {
public:
    Speed();
    ~Speed();

    /**
     * @brief Converts a speed value from one unit to another.
     * @param value The value to convert.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted speed value.
     */
    double convert(double value, SpeedUnit fromUnit, SpeedUnit toUnit);

    /**
     * @brief Converts a speed unit to its string representation.
     * @param unit The speed unit.
     * @return The string representation of the speed unit.
     */
    std::string toString(SpeedUnit unit);

private:
    std::array<std::string, 5> m_speedData;
    static const constexpr std::string_view SPEED {"speed"};
    System::EngineController engineController;
};

/**
 * @brief The enumeration representing different energy units.
 */
enum class EnergyUnit
{
    Joule,              //!< Joule
    Kilojoule,          //!< Kilojoule
    Calorie,            //!< Calorie
    Kilocalorie,        //!< Kilocalorie
    ElectronVolt,       //!< Electron volt
    BritishThermalUnit, //!< British Thermal Unit (BTU)
    FootPound,          //!< Foot-Pound
    Erg                 //!< Erg
};

/**
 * @brief The EnergyConverter class for converting energy values between different units.
 */
class Energy : public Abstracts::Convertor::UnitConverter<EnergyUnit> {
public:
    Energy();
    ~Energy();

    /**
     * @brief Converts an energy value from one unit to another.
     * @param value The value to convert.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted energy value.
     */
    double convert(double value, EnergyUnit fromUnit, EnergyUnit toUnit);

    /**
     * @brief Converts an energy unit to its string representation.
     * @param unit The energy unit.
     * @return The string representation of the energy unit.
     */
    std::string toString(EnergyUnit unit);

private:
    std::array<std::string, 8> m_energyData;
    static const constexpr std::string_view ENERGY {"energy"};
    System::EngineController engineController;
};


/**
 * @brief The enumeration representing different power units.
 */
enum class PowerUnit
{
    Watt,              //!< Watt
    Kilowatt,          //!< Kilowatt
    Megawatt,          //!< Megawatt
    Gigawatt,          //!< Gigawatt
    Horsepower,        //!< Horsepower
    FootPoundPerMinute //!< Foot-Pound per minute
};

/**
 * @brief The PowerConverter class for converting power values between different units.
 */
class Power : public Abstracts::Convertor::UnitConverter<PowerUnit> {
public:
    Power();
    ~Power();
    /**
     * @brief Converts a power value from one unit to another.
     * @param value The value to convert.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted power value.
     */
    double convert(double value, PowerUnit fromUnit, PowerUnit toUnit);

    /**
     * @brief Converts a power unit to its string representation.
     * @param unit The power unit.
     * @return The string representation of the power unit.
     */
    std::string toString(PowerUnit unit);

private:
    std::array<std::string, 6> m_powerData;
    static const constexpr std::string_view POWER {"power"};
    System::EngineController engineController;
};

/**
 * @brief The enumeration representing different pressure units.
 */
enum class PressureUnit
{
    Pascal,             //!< Pascal
    Kilopascal,         //!< Kilopascal
    Megapascal,         //!< Megapascal
    Bar,                //!< Bar
    Millibar,           //!< Millibar
    PoundPerSquareInch, //!< Pound per square inch (psi)
    Atmosphere,         //!< Atmosphere
    Torr                //!< Torr
};

/**
 * @brief The PressureConverter class for converting pressure values between different units.
 */
class Pressure : public Abstracts::Convertor::UnitConverter<PressureUnit> {
public:
    Pressure();
    ~Pressure();
    /**
     * @brief Converts a pressure value from one unit to another.
     * @param value The value to convert.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted pressure value.
     */
    double convert(double value, PressureUnit fromUnit, PressureUnit toUnit);

    /**
     * @brief Converts a pressure unit to its string representation.
     * @param unit The pressure unit.
     * @return The string representation of the pressure unit.
     */
    std::string toString(PressureUnit unit);

private:
    std::array<std::string, 8> m_pressureData;
    static const constexpr std::string_view PRESSURE {"pressure"};
    System::EngineController engineController;
};

/**
 * @brief The enumeration representing different angle units.
 */
enum class AngleUnit
{
    Degree,     //!< Degree
    Radian,     //!< Radian
    Grad,       //!< Grad
    Minute,     //!< Minute of arc
    Second,     //!< Second of arc
    Revolution  //!< Revolution
};

/**
 * @brief The AngleConverter class for converting angle values between different units.
 */
class Angle : public Abstracts::Convertor::UnitConverter<AngleUnit> {
public:
    Angle();
    ~Angle();
    /**
     * @brief Converts an angle value from one unit to another.
     * @param value The value to convert.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted angle value.
     */
    double convert(double value, AngleUnit fromUnit, AngleUnit toUnit);

    /**
     * @brief Converts an angle unit to its string representation.
     * @param unit The angle unit.
     * @return The string representation of the angle unit.
     */
    std::string toString(AngleUnit unit);

private:
    std::array<std::string, 6> m_angleData;
    static const constexpr std::string_view ANGLE {"angle"};
    System::EngineController engineController;
};

/**
 * @brief The enumeration representing different currency units.
 */
enum class CurrencyUnit
{
    USD,    //!< United States Dollar
    EUR,    //!< Euro
    GBP,    //!< British Pound
    JPY,    //!< Japanese Yen
    CAD,    //!< Canadian Dollar
    AUD,    //!< Australian Dollar
    CHF,    //!< Swiss Franc
    CNY,    //!< Chinese Yuan
    SEK,    //!< Swedish Krona
    NZD,    //!< New Zealand Dollar
    IRR,    //!< Iranian Rial
    INR,    //!< Indian Rupee
    MXN     //!< Mexican Peso
};

/**
 * @brief The CurrencyConverter class for converting currency values between different units.
 */
class Currency : public Abstracts::Convertor::UnitConverter<CurrencyUnit>
{
public:
    Currency();
    ~Currency();

    /**
     * @brief Converts a currency value from one unit to another.
     * @param value The value to convert.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted currency value.
     */
    double convert(double value, CurrencyUnit fromUnit, CurrencyUnit toUnit);

    /**
     * @brief Converts a currency unit to its string representation.
     * @param unit The currency unit.
     * @return The string representation of the currency unit.
     */
    std::string toString(CurrencyUnit unit);

private:
    std::array<std::string, 13> m_currencyData;
    static const constexpr std::string_view CURRENCY {"currency"};
    System::EngineController engineController;
};

enum class VolumeUnit
{
    CubicMeter,         //!< Cubic meter
    CubicKilometer,     //!< Cubic kilometer
    CubicCentimeter,    //!< Cubic centimeter
    CubicMillimeter,    //!< Cubic millimeter
    Liter,              //!< Liter
    Milliliter,         //!< Milliliter
    USGallon,           //!< US gallon
    USDryGallon,        //!< US dry gallon
    ImperialGallon,     //!< Imperial gallon
    ImperialQuart,      //!< Imperial quart
    ImperialPint,       //!< Imperial pint
    ImperialCup,        //!< Imperial cup
    ImperialFluidOunce, //!< Imperial fluid ounce
    ImperialTablespoon, //!< Imperial tablespoon
    ImperialTeaspoon    //!< Imperial teaspoon
};

class Volume : public Abstracts::Convertor::UnitConverter<VolumeUnit>
{
public:
    Volume();
    ~Volume();

    /**
     * @brief Converts a volume value from one unit to another.
     * @param value The value to be converted.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted value.
     */
    double convert(double value, VolumeUnit fromUnit, VolumeUnit toUnit) __cell_override;

    /**
     * @brief Returns the string representation of a volume unit.
     * @param unit The volume unit.
     * @return The string representation of the unit.
     */
    std::string toString(VolumeUnit unit) __cell_override;

private:
    std::array<std::string, 15> m_volumeData;
    static const constexpr std::string_view VOLUME {"volume"};
    System::EngineController engineController;
};

enum class FrequencyUnit {
    Hertz,         //!< Hertz unit
    Kilohertz,     //!< Kilohertz unit
    Megahertz,     //!< Megahertz unit
    Gigahertz,     //!< Gigahertz unit
    Terahertz      //!< Terahertz unit
};

/**
 * @class Frequency
 * @brief Class for frequency conversion.
 *
 * This class provides functionality to convert values between different frequency units.
 */
class Frequency : public Abstracts::Convertor::UnitConverter<VolumeUnit>
{
public:
    /**
     * @brief Default constructor.
     */
    Frequency();

    /**
     * @brief Destructor.
     */
    ~Frequency();

    /**
     * @brief Converts a value from one frequency unit to another.
     * @param value The value to be converted.
     * @param fromUnit The source frequency unit.
     * @param toUnit The target frequency unit.
     * @return The converted value.
     */
    double convert(double value, FrequencyUnit fromUnit, FrequencyUnit toUnit);

    /**
     * @brief Converts a frequency unit to its string representation.
     * @param unit The frequency unit.
     * @return The string representation of the unit.
     */
    std::string toString(FrequencyUnit unit);

private:
    std::array<std::string, 6> m_frequencyData;        //!< Frequency data
    static const constexpr std::string_view FREQUENCY {"frequency"};  //!< Frequency string
    System::EngineController engineController;
};

CELL_NAMESPACE_END

#endif  // CELL_UNIT_CONVERTOR_HPP
