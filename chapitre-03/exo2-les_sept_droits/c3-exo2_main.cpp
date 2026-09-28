#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKTime/NkClock.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

static NkWindowConfig Make(const char *title, int index) {
    NkWindowConfig cfg;
    cfg.title = title;
    cfg.width = 400;
    cfg.height = 300;
    cfg.x = 50 + index * 60;
    cfg.y = 50 + index * 60;
    return cfg;
}

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig c0 = Make("1 frame=false", 0);         c0.frame = false;
    NkWindowConfig c1 = Make("2 resizable=false", 1);     c1.resizable = false;
    NkWindowConfig c2 = Make("3 minimizable=false", 2);   c2.minimizable = false;
    NkWindowConfig c3 = Make("4 movable=false", 3);       c3.movable = false;
    NkWindowConfig c4 = Make("5 closable=false", 4);      c4.closable = false;
    NkWindowConfig c5 = Make("6 maximizable=false", 5);   c5.maximizable = false;
    NkWindowConfig c6 = Make("7 canFullscreen=false", 6); c6.canFullscreen = false;

    NkWindow w0(c0), w1(c1), w2(c2), w3(c3), w4(c4), w5(c5), w6(c6);

    bool running = true;
    NkEventSystem &events = NkEvents();
    events.AddEventCallback<NkWindowCloseEvent>([&](NkWindowCloseEvent *) { running = false; });
    events.AddEventCallback<NkKeyPressEvent>([&](NkKeyPressEvent *e) {
        if (e->GetKey() == NkKey::NK_ESCAPE) running = false;
    });

    while (running) {
        events.PollEvents();
        NkClock::Sleep((int64)10);
    }
    return 0;
}