#if __has_include("units.hpp")
#   include "units.hpp"
#else
#   error "Cell's "convertor.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Convertor::Units)

double Length::convert(double value, LengthUnit fromUnit, LengthUnit toUnit)
{
    __cell_static_const std::unordered_map<LengthUnit, double> conversionFactors = {
        { LengthUnit::Meter, 1.0 },
        { LengthUnit::Kilometer, 1000.0 },
        { LengthUnit::Centimeter, 0.01 },
        { LengthUnit::Millimeter, 0.001 },
        { LengthUnit::Micrometer, 0.000001 },
        { LengthUnit::Nanometer, 0.000000001 },
        { LengthUnit::Mile, 1609.34 },
        { LengthUnit::Yard, 0.9144 },
        { LengthUnit::Foot, 0.3048 },
        { LengthUnit::Inch, 0.0254 },
        { LengthUnit::LightYear, 9.461e15 }
    };

    double meters = value * conversionFactors.at(fromUnit);
    return meters / conversionFactors.at(toUnit);
}

std::string Length::toString(LengthUnit unit)
{
    switch (unit) {
    case LengthUnit::Meter:
        return "meter";
    case LengthUnit::Kilometer:
        return "kilometer";
    case LengthUnit::Centimeter:
        return "centimeter";
    case LengthUnit::Millimeter:
        return "millimeter";
    case LengthUnit::Micrometer:
        return "micrometer";
    case LengthUnit::Nanometer:
        return "nanometer";
    case LengthUnit::Mile:
        return "mile";
    case LengthUnit::Yard:
        return "yard";
    case LengthUnit::Foot:
        return "foot";
    case LengthUnit::Inch:
        return "inch";
    case LengthUnit::LightYear:
        return "light year";
    default:
        return "unknown";
    }
}

double Temperature::convert(double value, TemperatureUnit fromUnit, TemperatureUnit toUnit)
{
    if (fromUnit == toUnit) {
        return value;  // No conversion needed if units are the same
    }

    // Convert to Celsius first
    double celsiusValue = 0.0;
    switch (fromUnit) {
    case TemperatureUnit::Celsius:
        celsiusValue = value;
        break;
    case TemperatureUnit::Fahrenheit:
        celsiusValue = (value - 32.0) * 5.0 / 9.0;
        break;
    case TemperatureUnit::Kelvin:
        celsiusValue = value - 273.15;
        break;
    }

    // Convert from Celsius to the target unit
    double convertedValue = 0.0;
    switch (toUnit) {
    case TemperatureUnit::Celsius:
        convertedValue = celsiusValue;
        break;
    case TemperatureUnit::Fahrenheit:
        convertedValue = celsiusValue * 9.0 / 5.0 + 32.0;
        break;
    case TemperatureUnit::Kelvin:
        convertedValue = celsiusValue + 273.15;
        break;
    }

    return convertedValue;
}

std::string Temperature::toString(TemperatureUnit unit)
{
    switch (unit) {
    case TemperatureUnit::Celsius:
        return "Celsius";
    case TemperatureUnit::Fahrenheit:
        return "Fahrenheit";
    case TemperatureUnit::Kelvin:
        return "Kelvin";
    default:
        return "Unknown";
    }
}

double Area::convert(double value, AreaUnit fromUnit, AreaUnit toUnit)
{
    if (fromUnit == toUnit) {
        return value;  // No conversion needed if units are the same
    }

    __cell_static_const std::unordered_map<AreaUnit, double> conversionFactors = {
        { AreaUnit::SquareMeter, 1.0 },
        { AreaUnit::SquareKilometer, 1.0e6 },
        { AreaUnit::SquareCentimeter, 1.0e-4 },
        { AreaUnit::SquareMillimeter, 1.0e-6 },
        { AreaUnit::SquareMicrometer, 1.0e-12 },
        { AreaUnit::Hectare, 1.0e4 },
        { AreaUnit::SquareMile, 2.59e6 },
        { AreaUnit::SquareYard, 0.836 },
        { AreaUnit::SquareFoot, 0.093 },
        { AreaUnit::SquareInch, 0.000645 },
        { AreaUnit::Acre, 4046.86 }
    };

    double squareMeters = value * conversionFactors.at(fromUnit);
    return squareMeters / conversionFactors.at(toUnit);
}

std::string Area::toString(AreaUnit unit)
{
    switch (unit) {
    case AreaUnit::SquareMeter:
        return "Square meter";
    case AreaUnit::SquareKilometer:
        return "Square kilometer";
    case AreaUnit::SquareCentimeter:
        return "Square centimeter";
    case AreaUnit::SquareMillimeter:
        return "Square millimeter";
    case AreaUnit::SquareMicrometer:
        return "Square micrometer";
    case AreaUnit::Hectare:
        return "Hectare";
    case AreaUnit::SquareMile:
        return "Square mile";
    case AreaUnit::SquareYard:
        return "Square yard";
    case AreaUnit::SquareFoot:
        return "Square foot";
    case AreaUnit::SquareInch:
        return "Square inch";
    case AreaUnit::Acre:
        return "Acre";
    default:
        return "Unknown";
    }
}

double Weight::convert(double value, WeightUnit fromUnit, WeightUnit toUnit)
{
    if (fromUnit == toUnit) {
        return value;  // No conversion needed if units are the same
    }

    __cell_static_const std::unordered_map<WeightUnit, double> conversionFactors = {
        { WeightUnit::Kilogram, 1.0 },
        { WeightUnit::Gram, 0.001 },
        { WeightUnit::Milligram, 1.0e-6 },
        { WeightUnit::Microgram, 1.0e-9 },
        { WeightUnit::MetricTon, 1000.0 },
        { WeightUnit::LongTon, 1016.05 },
        { WeightUnit::ShortTon, 907.185 },
        { WeightUnit::Pound, 0.453592 },
        { WeightUnit::Ounce, 0.0283495 },
        { WeightUnit::Carrat, 0.0002 },
        { WeightUnit::AtomicMassUnit, 1.66054e-27 }
    };

    double kilograms = value * conversionFactors.at(fromUnit);
    return kilograms / conversionFactors.at(toUnit);
}

std::string Weight::toString(WeightUnit unit)
{
    switch (unit) {
    case WeightUnit::Kilogram:
        return "Kilogram";
    case WeightUnit::Gram:
        return "Gram";
    case WeightUnit::Milligram:
        return "Milligram";
    case WeightUnit::Microgram:
        return "Microgram";
    case WeightUnit::MetricTon:
        return "Metric ton";
    case WeightUnit::LongTon:
        return "Long ton";
    case WeightUnit::ShortTon:
        return "Short ton";
    case WeightUnit::Pound:
        return "Pound";
    case WeightUnit::Ounce:
        return "Ounce";
    case WeightUnit::Carrat:
        return "Carrat";
    case WeightUnit::AtomicMassUnit:
        return "Atomic mass unit";
    default:
        return "Unknown";
    }
}

double Time::convert(double value, TimeUnit fromUnit, TimeUnit toUnit)
{
    // Define the conversion factors between different time units
    __cell_static_const std::unordered_map<TimeUnit, double> conversionFactors = {
        { TimeUnit::Second, 1.0 },
        { TimeUnit::Millisecond, 0.001 },
        { TimeUnit::Microsecond, 1.0e-6 },
        { TimeUnit::Nanosecond, 1.0e-9 },
        { TimeUnit::Picosecond, 1.0e-12 },
        { TimeUnit::Minute, 60.0 },
        { TimeUnit::Hour, 3600.0 },
        { TimeUnit::Day, 86400.0 },
        { TimeUnit::Week, 604800.0 },
        { TimeUnit::Month, 2.628e+6 },
        { TimeUnit::Year, 3.154e+7 }
    };

    double seconds = value * conversionFactors.at(fromUnit);
    return seconds / conversionFactors.at(toUnit);
}

std::string Time::toString(TimeUnit unit)
{
    switch (unit) {
    case TimeUnit::Second:
        return "Second";
    case TimeUnit::Millisecond:
        return "Millisecond";
    case TimeUnit::Microsecond:
        return "Microsecond";
    case TimeUnit::Nanosecond:
        return "Nanosecond";
    case TimeUnit::Picosecond:
        return "Picosecond";
    case TimeUnit::Minute:
        return "Minute";
    case TimeUnit::Hour:
        return "Hour";
    case TimeUnit::Day:
        return "Day";
    case TimeUnit::Week:
        return "Week";
    case TimeUnit::Month:
        return "Month";
    case TimeUnit::Year:
        return "Year";
    default:
        return "Unknown";
    }
}

double Speed::convert(double value, SpeedUnit fromUnit, SpeedUnit toUnit)
{
    __cell_static_const std::unordered_map<SpeedUnit, double> conversionFactors = {
        { SpeedUnit::MeterPerSecond, 1.0 },
        { SpeedUnit::KilometerPerHour, 0.277778 },
        { SpeedUnit::MilePerHour, 0.44704 },
        { SpeedUnit::FootPerSecond, 0.3048 },
        { SpeedUnit::Knot, 0.514444 }
    };

    double metersPerSecond = value * conversionFactors.at(fromUnit);
    return metersPerSecond / conversionFactors.at(toUnit);
}

std::string Speed::toString(SpeedUnit unit)
{
    switch (unit) {
    case SpeedUnit::MeterPerSecond:
        return "meter/second";
    case SpeedUnit::KilometerPerHour:
        return "kilometer/hour";
    case SpeedUnit::MilePerHour:
        return "mile/hour";
    case SpeedUnit::FootPerSecond:
        return "foot/second";
    case SpeedUnit::Knot:
        return "knot";
    default:
        return "unknown";
    }
}

double Energy::convert(double value, EnergyUnit fromUnit, EnergyUnit toUnit)
{
    __cell_static_const std::unordered_map<EnergyUnit, double> conversionFactors = {
        { EnergyUnit::Joule, 1.0 },
        { EnergyUnit::Kilojoule, 1000.0 },
        { EnergyUnit::Calorie, 4.184 },
        { EnergyUnit::Kilocalorie, 4184.0 },
        { EnergyUnit::ElectronVolt, 1.6022e-19 },
        { EnergyUnit::BritishThermalUnit, 1055.0 },
        { EnergyUnit::FootPound, 1.3558 },
        { EnergyUnit::Erg, 1e-7 }
    };

    double joules = value * conversionFactors.at(fromUnit);
    return joules / conversionFactors.at(toUnit);
}

std::string Energy::toString(EnergyUnit unit)
{
    switch (unit) {
    case EnergyUnit::Joule:
        return "Joule";
    case EnergyUnit::Kilojoule:
        return "Kilojoule";
    case EnergyUnit::Calorie:
        return "Calorie";
    case EnergyUnit::Kilocalorie:
        return "Kilocalorie";
    case EnergyUnit::ElectronVolt:
        return "Electron Volt";
    case EnergyUnit::BritishThermalUnit:
        return "British Thermal Unit";
    case EnergyUnit::FootPound:
        return "Foot-Pound";
    case EnergyUnit::Erg:
        return "Erg";
    default:
        return "unknown";
    }
}

double Power::convert(double value, PowerUnit fromUnit, PowerUnit toUnit)
{
    __cell_static_const std::unordered_map<PowerUnit, double> conversionFactors = {
        { PowerUnit::Watt, 1.0 },
        { PowerUnit::Kilowatt, 1000.0 },
        { PowerUnit::Megawatt, 1e6 },
        { PowerUnit::Gigawatt, 1e9 },
        { PowerUnit::Horsepower, 745.7 },
        { PowerUnit::FootPoundPerMinute, 0.0226 }
    };

    double watts = value * conversionFactors.at(fromUnit);
    return watts / conversionFactors.at(toUnit);
}

std::string Power::toString(PowerUnit unit)
{
    switch (unit) {
    case PowerUnit::Watt:
        return "Watt";
    case PowerUnit::Kilowatt:
        return "Kilowatt";
    case PowerUnit::Megawatt:
        return "Megawatt";
    case PowerUnit::Gigawatt:
        return "Gigawatt";
    case PowerUnit::Horsepower:
        return "Horsepower";
    case PowerUnit::FootPoundPerMinute:
        return "Foot-Pound per minute";
    default:
        return "unknown";
    }
}

double Pressure::convert(double value, PressureUnit fromUnit, PressureUnit toUnit)
{
    __cell_static_const std::unordered_map<PressureUnit, double> conversionFactors = {
        { PressureUnit::Pascal, 1.0 },
        { PressureUnit::Kilopascal, 1000.0 },
        { PressureUnit::Megapascal, 1e6 },
        { PressureUnit::Bar, 1e5 },
        { PressureUnit::Millibar, 100.0 },
        { PressureUnit::PoundPerSquareInch, 6894.76 },
        { PressureUnit::Atmosphere, 101325.0 },
        { PressureUnit::Torr, 133.322 }
    };

    double pascals = value * conversionFactors.at(fromUnit);
    return pascals / conversionFactors.at(toUnit);
}

std::string Pressure::toString(PressureUnit unit)
{
    switch (unit) {
    case PressureUnit::Pascal:
        return "Pascal";
    case PressureUnit::Kilopascal:
        return "Kilopascal";
    case PressureUnit::Megapascal:
        return "Megapascal";
    case PressureUnit::Bar:
        return "Bar";
    case PressureUnit::Millibar:
        return "Millibar";
    case PressureUnit::PoundPerSquareInch:
        return "Pound per square inch (psi)";
    case PressureUnit::Atmosphere:
        return "Atmosphere";
    case PressureUnit::Torr:
        return "Torr";
    default:
        return "unknown";
    }
}

double Angle::convert(double value, AngleUnit fromUnit, AngleUnit toUnit)
{
    __cell_static_const std::unordered_map<AngleUnit, double> conversionFactors = {
        { AngleUnit::Degree, 1.0 },
        { AngleUnit::Radian, 57.2958 },
        { AngleUnit::Grad, 0.9 },
        { AngleUnit::Minute, 0.0167 },
        { AngleUnit::Second, 0.0003 },
        { AngleUnit::Revolution, 360.0 }
    };

    double degrees = value * conversionFactors.at(fromUnit);
    return degrees / conversionFactors.at(toUnit);
}

std::string Angle::toString(AngleUnit unit)
{
    switch (unit) {
    case AngleUnit::Degree:
        return "Degree";
    case AngleUnit::Radian:
        return "Radian";
    case AngleUnit::Grad:
        return "Grad";
    case AngleUnit::Minute:
        return "Minute of arc";
    case AngleUnit::Second:
        return "Second of arc";
    case AngleUnit::Revolution:
        return "Revolution";
    default:
        return "unknown";
    }
}

double Currency::convert(double value, CurrencyUnit fromUnit, CurrencyUnit toUnit)
{
    // Placeholder implementation - Fetch exchange rates from an external data source
    // and perform the conversion based on the current rates.
    // Replace this code with your actual implementation.

    //! Todo based on external api.
    //! This is an concept usage.

    __cell_static_const std::unordered_map<CurrencyUnit, double> conversionFactors = {
        { CurrencyUnit::USD, 1.0 },
        { CurrencyUnit::EUR, 1.2 },
        { CurrencyUnit::GBP, 1.4 },
        { CurrencyUnit::JPY, 0.008 },
        { CurrencyUnit::CAD, 0.8 },
        { CurrencyUnit::AUD, 0.75 },
        { CurrencyUnit::CHF, 1.1 },
        { CurrencyUnit::CNY, 0.15 },
        { CurrencyUnit::SEK, 0.11 },
        { CurrencyUnit::NZD, 0.7 },
        { CurrencyUnit::INR, 0.013 },
        { CurrencyUnit::MXN, 0.045 },
        { CurrencyUnit::IRR, 522420 }
    };

    double usdValue = value / conversionFactors.at(fromUnit);
    return usdValue * conversionFactors.at(toUnit);
}

std::string Currency::toString(CurrencyUnit unit)
{
    switch (unit) {
    case CurrencyUnit::USD:
        return "United States Dollar";
    case CurrencyUnit::EUR:
        return "Euro";
    case CurrencyUnit::GBP:
        return "British Pound";
    case CurrencyUnit::JPY:
        return "Japanese Yen";
    case CurrencyUnit::CAD:
        return "Canadian Dollar";
    case CurrencyUnit::AUD:
        return "Australian Dollar";
    case CurrencyUnit::CHF:
        return "Swiss Franc";
    case CurrencyUnit::CNY:
        return "Chinese Yuan";
    case CurrencyUnit::SEK:
        return "Swedish Krona";
    case CurrencyUnit::NZD:
        return "New Zealand Dollar";
    case CurrencyUnit::INR:
        return "Indian Rupee";
    case CurrencyUnit::MXN:
        return "Mexican Peso";
    case CurrencyUnit::IRR:
        return "Iranian Rial";
    default:
        return "Unknown";
    }
}

double Volume::convert(double value, VolumeUnit fromUnit, VolumeUnit toUnit)
{
    __cell_static_const std::unordered_map<VolumeUnit, double> conversionFactors = {
        { VolumeUnit::CubicMeter, 1.0 },
        { VolumeUnit::CubicKilometer, 1e9 },
        { VolumeUnit::CubicCentimeter, 0.000001 },
        { VolumeUnit::CubicMillimeter, 0.000000001 },
        { VolumeUnit::Liter, 0.001 },
        { VolumeUnit::Milliliter, 0.000001 },
        { VolumeUnit::USGallon, 0.00378541 },
        { VolumeUnit::USDryGallon, 0.00440488 },
        { VolumeUnit::ImperialGallon, 0.00454609 },
        { VolumeUnit::ImperialQuart, 0.00113652 },
        { VolumeUnit::ImperialPint, 0.000568261 },
        { VolumeUnit::ImperialCup, 0.000284131 },
        { VolumeUnit::ImperialFluidOunce, 0.0000284131 },
        { VolumeUnit::ImperialTablespoon, 0.0000177582 },
        { VolumeUnit::ImperialTeaspoon, 0.00000591939 }
    };

    double cubicMeters = value * conversionFactors.at(fromUnit);
    return cubicMeters / conversionFactors.at(toUnit);
}

std::string Volume::toString(VolumeUnit unit)
{
    switch (unit) {
    case VolumeUnit::CubicMeter:
        return "cubic meter";
    case VolumeUnit::CubicKilometer:
        return "cubic kilometer";
    case VolumeUnit::CubicCentimeter:
        return "cubic centimeter";
    case VolumeUnit::CubicMillimeter:
        return "cubic millimeter";
    case VolumeUnit::Liter:
        return "liter";
    case VolumeUnit::Milliliter:
        return "milliliter";
    case VolumeUnit::USGallon:
        return "US gallon";
    case VolumeUnit::USDryGallon:
        return "US dry gallon";
    case VolumeUnit::ImperialGallon:
        return "imperial gallon";
    case VolumeUnit::ImperialQuart:
        return "imperial quart";
    case VolumeUnit::ImperialPint:
        return "imperial pint";
    case VolumeUnit::ImperialCup:
        return "imperial cup";
    case VolumeUnit::ImperialFluidOunce:
        return "imperial fluid ounce";
    case VolumeUnit::ImperialTablespoon:
        return "imperial tablespoon";
    case VolumeUnit::ImperialTeaspoon:
        return "imperial teaspoon";
    default:
        return "unknown";
    }
}

CELL_NAMESPACE_END
