#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "La fenetre nue";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsValid()) {
        logger.Error("[LaFenetreNue] Creation fenetre KO");
        return 1;
    }

    while (window.IsOpen()) {
        NkEvents().PollEvents();
    }

    window.Close();
    return 0;
}