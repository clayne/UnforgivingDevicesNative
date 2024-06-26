#include <UD_Skill.h>
#include <UD_Utility.h>
#include <UD_Config.h>

namespace UD
{
    int CalculateSkillFromPerks(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, RE::BGSListForm* a_formlist, int a_increase)
    {
        if (a_actor == nullptr || a_formlist == nullptr) return 10;

        LOG("CalculateSkillFromPerks called a_actor={},a_formlist={}",reinterpret_cast<uintptr_t>(a_actor),reinterpret_cast<uintptr_t>(a_formlist))

        int loc_res = 0;
        //LOG("Checking persist forms")
        for (auto&& it : a_formlist->forms)
        {
            if (it != nullptr)
            {
                RE::BGSPerk* loc_perk = it->As<RE::BGSPerk>();
                //LOG("Checking perk {}",loc_perk->GetName());
                if ((loc_perk != nullptr) && a_actor->HasPerk(loc_perk))
                {
                    loc_res += a_increase;
                }
            }
        }

        if ((a_formlist->scriptAddedFormCount > 0U) && (a_formlist->scriptAddedTempForms != nullptr))
        {
            auto loc_forms = *a_formlist->scriptAddedTempForms;
            //LOG("Checking temp forms")
            for (uint32_t i = 0; i < a_formlist->scriptAddedFormCount; i++)
            {
                
                RE::TESForm* loc_form = RE::TESForm::LookupByID(loc_forms[i]);
                if (loc_form != nullptr)
                {
                    RE::BGSPerk* loc_perk = loc_form->As<RE::BGSPerk>();
                    //LOG("Checking perk {}",loc_perk->GetName());
                    if ((loc_perk != nullptr) && a_actor->HasPerk(loc_perk))
                    {
                        loc_res += a_increase;
                    }
                }
            }
        }

        return loc_res;
    }
}