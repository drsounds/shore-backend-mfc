#pragma once

#include <afxext.h>
#include <afxwin.h>
#include <map>
#include <shore/frame.h>
#include "mfc_canvas.h"

namespace shore {
namespace backend {
namespace mfc {

class MfcFrame : public CFrameWnd {
public:
    explicit MfcFrame(SHFrame* frame) : frame_(frame) {}
    CMenu menuBar;
    CToolBar toolBar;
    CStatusBar statusBar;
    std::map<std::string, CMenu*> menus;
protected:
    afx_msg int OnCreate(LPCREATESTRUCT createStruct);
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* dc);
    afx_msg void OnLButtonDown(UINT flags, CPoint point);
    afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
public:
    static const UINT kBase = 0x8000;
    SHFrame* Frame() const { return frame_; }
private:
    SHFrame* frame_;
};

}  // namespace mfc
}  // namespace backend
}