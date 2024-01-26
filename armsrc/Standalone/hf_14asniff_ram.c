#include "standalone.h"
#include "proxmark3_arm.h"
#include "iso14443a.h"
#include "util.h"
#include "appmain.h"
#include "dbprint.h"
#include "ticks.h"
#include "BigBuf.h"

void ModInfo(void) {
    DbpString("hf_14asniff_ram: standalone 'hf 14a sniff', keeps it in memory");
}

void RunMod() {
    StandAloneMode();
    Dbprintf("Starting standalone mode: hf_14asniff_ram");

    for (;;) {
        SniffIso14443a(0);
        
        LED_D_ON();
        for (;;) {
            WDT_HIT();
            int button_pressed = BUTTON_HELD(280);
            if (button_pressed == BUTTON_HOLD)
                break;

            // exit from Standalone Mode,   send a usbcommand.
            if (data_available()) return;
        }
        LED_D_OFF();
        SpinDelay(300);
    }
}
