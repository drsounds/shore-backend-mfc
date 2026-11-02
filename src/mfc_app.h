#pragma once

#include <afxwin.h>
#include <shore/app.h>

namespace shore {
namespace backend {
namespace mfc {

class MfcApp : public CWinApp {
public:
    SHApp* app = nullptr;
    BOOL InitInstance() override {
        if (!app->OnInit()) return FALSE;
        return TRUE;
    }
};

}  // namespace mfc
}  // namespace backend
}  // namespace shore