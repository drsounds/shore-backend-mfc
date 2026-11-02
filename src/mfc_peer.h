#pragma once

#include <afxcmn.h>
#include <afxwin.h>
#include <stdexcept>
#include <shore/backend.h>
#include <shore/frame.h>
#include <shore/toolbar.h>
#include "mfc.h"
#include "mfc_frame.h"

namespace shore {
namespace backend {
namespace mfc {

class MfcPeer : public SHFramePeer {
public:
    explicit MfcPeer(SHFrame* frame) : win_(new MfcFrame(frame)) {
        if (!win_->Create(nullptr, W(frame->Title()), WS_OVERLAPPEDWINDOW,
                          CRect(0, 0, frame->Width(), frame->Height()))) {
            delete win_;
            win_ = nullptr;
            throw std::runtime_error("MFC failed to create a Shore frame");
        }
        win_->menuBar.CreateMenu();
        win_->SetMenu(&win_->menuBar);
    }
    ~MfcPeer() override {
        if (win_ && ::IsWindow(win_->m_hWnd)) win_->DestroyWindow();
    }
    void SetTitle(const std::string& title) override { win_->SetWindowText(W(title)); }
    void SetStatusText(const std::string& text) override {
        if (::IsWindow(win_->statusBar.m_hWnd)) win_->statusBar.SetPaneText(0, W(text));
    }
    void AddMenuItem(const std::string& menu, const std::string& label, int id) override {
        CMenu*& m = win_->menus[menu];
        if (!m) {
            m = new CMenu;
            m->CreatePopupMenu();
            win_->menuBar.AppendMenu(MF_POPUP, reinterpret_cast<UINT_PTR>(m->m_hMenu), W(menu));
        }
        m->AppendMenu(MF_STRING, MfcFrame::kBase + id, W(label));
        win_->DrawMenuBar();
    }
    void SetToolBar(const SHToolBar& toolbar) override {
        if (!::IsWindow(win_->toolBar.m_hWnd))
            win_->toolBar.CreateEx(win_, TBSTYLE_FLAT | TBSTYLE_LIST, WS_CHILD | WS_VISIBLE | CBRS_TOP);
        CToolBarCtrl& ctrl = win_->toolBar.GetToolBarCtrl();
        while (ctrl.GetButtonCount() > 0) ctrl.DeleteButton(0);
        for (const auto& it : toolbar.Items()) {
            CString text = W(it.label);
            text.AppendChar(0);  // double-NUL terminated string for AddStrings
            TBBUTTON b = {};
            if (it.separator) { b.fsStyle = BTNS_SEP; }
            else {
                b.iBitmap = I_IMAGENONE;
                b.idCommand = MfcFrame::kBase + it.id;
                b.fsState = TBSTATE_ENABLED;
                b.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE | BTNS_SHOWTEXT;
                b.iString = ctrl.AddStrings(text);
            }
            ctrl.AddButtons(1, &b);
        }
        win_->RecalcLayout();
    }
    void Show(bool show) override {
        win_->ShowWindow(show ? SW_SHOW : SW_HIDE);
        if (show) win_->UpdateWindow();
    }
    void Invalidate() override { win_->Invalidate(); }
private:
    MfcFrame* win_;
};

}  // namespace mfc
}  // namespace backend
}  // namespace shore