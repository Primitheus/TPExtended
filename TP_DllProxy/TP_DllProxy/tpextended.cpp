#include "tpextended.h"

// Not Used Yet
Patch::Patch(DWORD address, std::string enabled, std::string disabled)
{

    this->active = false;
    this->address = address;
    this->enabled = enabled;
    this->disabled = disabled;

}


// Not Used Yet
void Patch::toggle()
{

    if (this->active)
        memapi::write(this->address, this->disabled);
    else
        memapi::write(this->address, this->enabled);

    this->active = !this->active;

}


std::string fillPattern(const std::string& pattern, int value) {

    unsigned char byte1 = value & 0xFF;       
    unsigned char byte2 = (value >> 8) & 0xFF;

    std::ostringstream ss;
    ss << std::hex << std::setfill('0');

    std::string newPattern = pattern;

    size_t pos = newPattern.find("x x");
    if (pos != std::string::npos) {
        ss << std::setw(2) << static_cast<int>(byte1) << " " << std::setw(2) << static_cast<int>(byte2);
        newPattern.replace(pos, 3, ss.str());
    }

    return newPattern;
}


void TPEXTENDED::Init(bool isMulticlient, int width, int height)
{
    DWORD dw_min = 0x400000;
    DWORD dw_max = 0x7FFFFF;
    
   if (isMulticlient)
   {
       this->Multiclient = Scanner::FindPattern(dw_min, dw_max, "75 1B 6A 00 68 20 18 7F 00");
       memapi::write(this->Multiclient, "EB 1B 6A 00 68 20 18 7F 00");

   }
   
   // Change Window Options
   this->WindowOpts = Scanner::FindPattern(dw_min, dw_max, "68 00 00 00 80 51");
   memapi::write(this->WindowOpts, "68 00 00 CF 00 51");

   // Set Resolution
   this->WinW = Scanner::FindPattern(dw_min, dw_max, "C7 44 24 2C 20 03 00 00");
   this->WinH = Scanner::FindPattern(dw_min, dw_max, "C7 44 24 30 58 02 00 00");

   std::string WinWPattern = fillPattern("C7 44 24 2C x x 00 00", width);
   std::string WinHPattern = fillPattern("C7 44 24 30 x x 00 00", height);

   std::cout << "WinW Pattern: " << WinWPattern << std::endl;
   std::cout << "WinH Pattern: " << WinHPattern << std::endl;

   memapi::write(this->WinW, WinWPattern);
   memapi::write(this->WinH, WinHPattern);

   // Mouse Fix for High DPI
   this->MouseFix = Scanner::FindPattern(dw_min, dw_max, "74 3C DE E9 85 D2");
   memapi::write(this->MouseFix, "75 3C DE E9 85 D2");


   // Remove FPS Limit When Tabbed Out
   this->RemoveFPSLimit1 = Scanner::FindPattern(dw_min, dw_max, "46 68 E8 03 00 00");
   memapi::write(this->RemoveFPSLimit1, "46 68 00 00 00 00");

   this->RemoveFPSLimit2 = Scanner::FindPattern(dw_min, dw_max, "4C 68 E8 03 00 00");
   memapi::write(this->RemoveFPSLimit2, "4C 68 00 00 00 00");

   this->RemoveFPSLimit3 = Scanner::FindPattern(dw_min, dw_max, "3A 68 E8 03 00 00 FF");
   memapi::write(this->RemoveFPSLimit3, "3A 68 00 00 00 00 FF");


}