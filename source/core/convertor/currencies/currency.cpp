#if __has_include("currency.hpp")
#   include "currency.hpp"
#else
#   error "Cell's "currency.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

#if __has_include("modules/settings/json.hpp")
#   include "modules/settings/json.hpp"
#else
#   error "Cell's "modules/settings/json.hpp" was not found!"
#endif


CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::Modules::BuiltIn::Settings;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::JSon;

CELL_NAMESPACE_BEGIN(Cell::Convertors::Currencies)

Currency::Currency()
{
    try {
        auto currentLang = createLanguageObject()->getLanguageCode();
        JSonValue items = safeEngine()->get()->translator().getLanguageSpec(currentLang);
        auto object = JsonFind(items, DIGITS);
        for (const auto& ks : object.getAsObject())
        {
            if(ks.key == UNIT_WORDS)
            {
                for(const auto& o : object.getAsArray(ks.value))
                {
                    units.push_back(object.getAsString(o));
                }
            }
            if(ks.key == TENS_WORDS)
            {
                for(const auto& o : object.getAsArray(ks.value))
                {
                    tens.push_back(object.getAsString(o));
                }
            }
            if(ks.key == DIGIT_WORDS)
            {
                for(const auto& o : object.getAsArray(ks.value))
                {
                    digitWords.push_back(object.getAsString(o));
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
}

std::string Currency::numberToText(Types::ullongInt number)
{
    auto meta = safeEngine()->meta();
    auto currentLang = createLanguageObject()->getLanguageCode();
    if (number < 20) {
        return units[number];
    } else if (number < 100) {
        int tensDigit = number / 10;
        int unitsDigit = number % 10;
        std::string text = tens[tensDigit];
        if (unitsDigit > 0) {
            auto items = safeEngine()->get()->translator().getLanguageSpec(currentLang);
            auto it = meta->getJsonObject<JSonValue>(items, meta->returnView(CURRENCIES));
            std::string mixedForm { meta->getJsonObject<std::string>(it, meta->returnView(VIEW_FORMAT), "currency_mixed_form") };
            text += mixedForm + units[unitsDigit];
        }
        return text;
    } else if (number < 1000) {
        std::string ustring;
        if (!digitWords.empty()) {
            ustring = digitWords[0]; // hundred
        }
        int hundredsDigit = number / 100;
        int tensAndUnits = number % 100;
        std::string text = units[hundredsDigit] + __cell_space + ustring;
        if (tensAndUnits > 0) {
            text += __cell_space + numberToText(tensAndUnits);
        }
        return text;
    } else if (number < 1000000) {
        std::string ustring;
        if (!digitWords.empty()) {
            ustring = digitWords[1]; // thousands
        }
        int thousands = number / 1000;
        int hundreds = number % 1000;
        std::string text = numberToText(thousands) + __cell_space + ustring;
        if (hundreds > 0) {
            text += __cell_space + numberToText(hundreds);
        }
        return text;
    } else if (number < 1000000000) {
        std::string ustring;
        if (!digitWords.empty()) {
            ustring = digitWords[2]; // millions
        }
        int millions = number / 1000000;
        int thousands = number % 1000000;
        std::string text = numberToText(millions) + __cell_space + ustring;
        if (thousands > 0) {
            text += __cell_space + numberToText(thousands);
        }
        return text;
    } else if (number < 1000000000000) {
        std::string ustring;
        if (!digitWords.empty()) {
            ustring = digitWords[3]; // billions
        }
        int billions = number / 1000000000;
        int millions = number % 1000000000;
        std::string text = numberToText(billions) + __cell_space + ustring;
        if (millions > 0) {
            text += __cell_space + numberToText(millions);
        }
        return text;
    } else {
        std::string ustring;
        if (!digitWords.empty()) {
            ustring = digitWords[4]; // trillions
        }
        int trillions = number / 1000000000000;
        int billions = number % 1000000000000;
        std::string text = numberToText(trillions) + __cell_space + ustring;
        if (billions > 0) {
            text += __cell_space + numberToText(billions);
        }
        return text;
    }
}

Types::OptionalString Currency::toWord(double amount)
{
    auto meta = safeEngine()->meta();
    llong baseUnit = static_cast<llong>(amount);
    const int subUnit = static_cast<int>((amount - baseUnit) * 100 + 0.5);

    auto currentLang        = createLanguageObject()->getLanguageCode();
    auto items              = safeEngine()->get()->translator().getLanguageSpec(currentLang);
    auto it                 = meta->getJsonObject<JSonValue>(items, meta->returnView(CURRENCIES));

    std::string baseUnitStr     { meta->getJsonObject<std::string>(it, meta->returnView(VIEW_FORMAT), meta->returnView(MIN_CURRENCY_UNIT))          };
    std::string andUnitStr      { meta->getJsonObject<std::string>(it, meta->returnView(VIEW_FORMAT), meta->returnView(CURRENCY_MIXED_FORM))        };
    std::string fractionalUnit  { meta->getJsonObject<std::string>(it, meta->returnView(VIEW_FORMAT), meta->returnView(FRACTIONAL_MONETARY_UNIT))   };

    std::string p = safeTranslate(currentLang,"core", "currency_plural_form");
    std::string pluralWord = p.c_str() ? __cell_space : __cell_null_str;

    std::string baseUnitText;
    if (baseUnit > 0) {
        baseUnitText = numberToText(baseUnit);
        baseUnitText += (baseUnit == 1) ? __cell_space + baseUnitStr : __cell_space + baseUnitStr + pluralWord;
    }
    std::string subUnitText;
    if (subUnit > 0) {
        subUnitText = numberToText(subUnit);
        subUnitText += (subUnit == 1) ? __cell_space + fractionalUnit : __cell_space + fractionalUnit + pluralWord;
    }
    std::string result;
    if (!baseUnitText.empty()) {
        result += baseUnitText;
    }
    if (!baseUnitText.empty() && !subUnitText.empty())
    {
        result += __cell_space +  andUnitStr + __cell_space;
    }
    if (!subUnitText.empty()) {
        result += subUnitText;
    }
    return result;
}

CELL_NAMESPACE_END

