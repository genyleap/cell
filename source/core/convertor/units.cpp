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
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::JSon;

CELL_NAMESPACE_BEGIN(Cell::Convertor::Units)

Length::Length()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == LENGTH)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_lengthData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_lengthData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Length::~Length()
{
    safeEngine()->meta()->clearContainer(m_lengthData);
}

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
        { LengthUnit::LightYear, 9.46073047258E+15 }
    };

    double meters = value * conversionFactors.at(fromUnit);
    return meters / conversionFactors.at(toUnit);
}

std::string Length::toString(LengthUnit unit)
{
    if (unit >= LengthUnit::Meter && unit <= LengthUnit::LightYear) {
        return m_lengthData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Temperature::Temperature()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == TEMPERATURE)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_temperatureData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_temperatureData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Temperature::~Temperature()
{
    safeEngine()->meta()->clearContainer(m_temperatureData);
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
    if (unit >= TemperatureUnit::Celsius && unit <= TemperatureUnit::Kelvin) {
        return m_temperatureData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Area::Area()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == AREA)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_areaData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_areaData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Area::~Area()
{
    safeEngine()->meta()->clearContainer(m_areaData);
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
    if (unit >= AreaUnit::SquareMeter && unit <= AreaUnit::Acre) {
        return m_areaData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Weight::Weight()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == WEIGHT)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_weightData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_weightData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Weight::~Weight()
{
    safeEngine()->meta()->clearContainer(m_weightData);
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
    if (unit >= WeightUnit::Kilogram && unit <= WeightUnit::AtomicMassUnit) {
        return m_weightData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Time::Time()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == TIME)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_timeData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_timeData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Time::~Time()
{
    safeEngine()->meta()->clearContainer(m_timeData);
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
    if (unit >= TimeUnit::Second && unit <= TimeUnit::Year) {
        return m_timeData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Speed::Speed()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == SPEED)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_speedData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_speedData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Speed::~Speed()
{
    safeEngine()->meta()->clearContainer(m_speedData);
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
    if (unit >= SpeedUnit::MeterPerSecond && unit <= SpeedUnit::Knot) {
        return m_speedData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Energy::Energy()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == ENERGY)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_energyData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_energyData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Energy::~Energy()
{
    safeEngine()->meta()->clearContainer(m_energyData);
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
    if (unit >= EnergyUnit::Joule && unit <= EnergyUnit::Erg) {
        return m_energyData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Power::Power()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == POWER)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_powerData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_powerData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Power::~Power()
{
    safeEngine()->meta()->clearContainer(m_powerData);
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
    if (unit >= PowerUnit::Watt && unit <= PowerUnit::FootPoundPerMinute) {
        return m_powerData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Pressure::Pressure()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == PRESSURE)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_pressureData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_pressureData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Pressure::~Pressure()
{
    safeEngine()->meta()->clearContainer(m_pressureData);
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
    if (unit >= PressureUnit::Pascal && unit <= PressureUnit::Torr) {
        return m_pressureData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Angle::Angle()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == ANGLE)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_angleData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_angleData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Angle::~Angle()
{
    safeEngine()->meta()->clearContainer(m_angleData);
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
    if (unit >= AngleUnit::Degree && unit <= AngleUnit::Revolution) {
        return m_angleData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Currency::Currency()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == CURRENCY)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_currencyData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_currencyData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Currency::~Currency()
{
    safeEngine()->meta()->clearContainer(m_currencyData);
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
    if (unit >= CurrencyUnit::USD && unit <= CurrencyUnit::MXN) {
        return m_currencyData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

Volume::Volume()
{
    auto meta           =   safeEngine()->meta();
    auto currentLang    =   createLanguageObject()->getLanguageCode();
    unitItems.items     =   safeEngine()->get()->translator().getLanguageSpec(currentLang);
    try {
        auto object = JsonFind(unitItems.items, UNITS);
        for (const auto& [key, value] : object.getAsObject())
        {
            if(key == VOLUME)
            {
                const auto& objectArray = object.getAsArray(value);
                for (std::size_t i = 0; i < objectArray.size() && i < m_volumeData.size(); ++i)
                {
                    const JSonValue& o = meta->getJsonObjectByIndex(value, i);
                    m_volumeData[i] = meta->returnJsonAt(o, meta->returnView(Translation::TRANSLATOR_CONSTANTS::DEFAULT_VALUE)).asString;
                }
            }
        }
    } catch (const Exception& e)
    {
        Log(e.what(), LoggerType::Critical);
    }
}

Volume::~Volume()
{
    safeEngine()->meta()->clearContainer(m_volumeData);
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
    if (unit >= VolumeUnit::CubicMeter && unit <= VolumeUnit::ImperialTeaspoon) {
        return m_volumeData[static_cast<Types::size>(unit)];
    } else {
        return "unknown";
    }
}

CELL_NAMESPACE_END
