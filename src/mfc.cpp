#include "mfc_app.h"
#include "mfc_backend_impl.h"
#include "mfc_frame.h"
#include "mfc_peer.h"
#include <shore-backend-mfc/backend.h>
#include <shore/view.h>

namespace shore {
namespace backend {
namespace mfc {

BEGIN_MESSAGE_MAP(MfcFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

int MfcFrame::OnCreate(LPCREATESTRUCT createStruct) {
    if (CFrameWnd::OnCreate(createStruct) == -1) return -1;
    const UINT indicators[] = {ID_SEPARATOR};
    if (!statusBar.Create(this) || !statusBar.SetIndicators(indicators, 1)) return -1;
    return 0;
}
void MfcFrame::OnPaint() {
    CPaintDC dc(this);
    CRect rect;
    GetClientRect(&rect);
    MfcCanvas canvas(dc, rect);
    frame_->Paint(canvas);
}
BOOL MfcFrame::OnEraseBkgnd(CDC* dc) {
    CRect rect;
    GetClientRect(&rect);
    dc->FillSolidRect(rect, RGB(255, 255, 255));
    return TRUE;
}
void MfcFrame::OnLButtonDown(UINT, CPoint point) {
    if (frame_->View()) frame_->View()->OnMouseDown(point.x, point.y);
}
BOOL MfcFrame::OnCommand(WPARAM wParam, LPARAM lParam) {
    UINT id = LOWORD(wParam);
    if (id >= kBase && frame_->Dispatch(static_cast<int>(id - kBase))) return TRUE;
    return CFrameWnd::OnCommand(wParam, lParam);
}

std::unique_ptr<SHFramePeer> MfcBackend::CreateFramePeer(SHFrame* frame) {
    return std::unique_ptr<SHFramePeer>(new MfcPeer(frame));
}
int MfcBackend::Run(SHApp* app, int, char**) {
    MfcApp mfc;
    mfc.app = app;
    if (!AfxWinInit(::GetModuleHandle(nullptr), nullptr, ::GetCommandLine(), SW_SHOW)) return 1;
    if (!mfc.InitInstance()) return 1;
    return mfc.Run();
}
void MfcBackend::Quit() { ::PostQuitMessage(0); }
const char* MfcBackend::Name() const { return "MFC"; }

std::unique_ptr<SHBackend> CreateBackend() {
    return std::unique_ptr<SHBackend>(new MfcBackend);
}

}  // namespace mfc
}  // namespace backend
}  // namespace shore
