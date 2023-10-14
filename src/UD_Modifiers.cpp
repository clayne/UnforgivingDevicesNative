#include <UD_Modifiers.h>


namespace UD 
{
    int GetStringParamInt(PAPYRUSFUNCHANDLE, std::string a_DataStr, int a_Index, int a_DefaultValue)
    {
        UDSKSELOG("GetStringParamInt({},{},{})",a_DataStr,a_Index,a_DefaultValue)
        return _GetModifierParam<int>(a_DataStr,a_Index,a_DefaultValue);
    }

    float GetStringParamFloat(PAPYRUSFUNCHANDLE, std::string a_DataStr, int a_Index, float a_DefaultValue)
    {
        UDSKSELOG("GetStringParamFloat({},{},{})",a_DataStr,a_Index,a_DefaultValue)
        return _GetModifierParam<float>(a_DataStr,a_Index,a_DefaultValue);
    }

    std::string GetStringParamString(PAPYRUSFUNCHANDLE, std::string a_DataStr, int a_Index, std::string a_DefaultValue)
    {
        UDSKSELOG("GetStringParamString({},{},{})",a_DataStr,a_Index,a_DefaultValue)
        return _GetModifierParam<std::string>(a_DataStr,a_Index,a_DefaultValue);
    }

    std::vector<std::string> GetModifierAllParam(PAPYRUSFUNCHANDLE, std::string a_param)
    {
        UDSKSELOG("GetModifierAllParam({})",a_param)
        return _GetModifierAllParam<std::string>(a_param);
    }

    template<class T>
    T _GetModifierParam(const std::string& a_param, int a_Index, T a_DefaultValue)
    {
        const std::vector<std::string> loc_para = _GetModifierAllParam<std::string>(a_param);

        if (a_Index < loc_para.size() && a_Index >= 0)
        {
            try
            {
                return ((loc_para[a_Index] != "") ? boost::lexical_cast<T>(loc_para[a_Index]) : a_DefaultValue);
            }
            catch(boost::bad_lexical_cast &)
            {
                UDSKSELOG("_GetModifierParam() - Error casting {} to {}",a_param,a_Index,a_DefaultValue,a_param,typeid(T).name())
                return a_DefaultValue;
            }
        }
        else
        {
            return a_DefaultValue;
        }
    }

    template<class T>
    std::vector<T> _GetModifierAllParam(const std::string& a_param)
    {
        //separete parameters
        std::vector<std::string> loc_params;
        boost::split(loc_params,a_param,boost::is_any_of(","));
    
        std::vector<T> loc_res;
        for (auto&& it : loc_params)
        {
            try
            {
                loc_res.push_back(boost::lexical_cast<T>(it));
            }
            catch(boost::bad_lexical_cast &)
            {
                UDSKSELOG("_GetModifierAllParam({}) - Error casting {} to {}",a_param,a_param,typeid(T).name())
                loc_res.push_back(T());
                continue;
            }
        }
        return loc_res;
    }


}