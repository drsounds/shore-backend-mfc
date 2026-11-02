#pragma once

#include <afxwin.h>
#include <shore/canvas.h>
#include "mfc.h"

namespace shore {
namespace backend {
namespace mfc {

class MfcCanvas : public SHCanvas {
public:
    MfcCanvas(CDC& dc, const CRect& rect) : dc_(dc), rect_(rect) {}
    int Width() const override { return rect_.Width(); }
    int Height() const override { return rect_.Height(); }
    void FillRect(int x, int y, int width, int height, SHColor color) override {
        CBrush brush(Col(color));
        dc_.FillRect(CRect(x, y, x + width, y + height), &brush);
    }
    void DrawLine(int x1, int y1, int x2, int y2, SHColor color) override {
        CPen pen(PS_SOLID, 1, Col(color));
        CPen* oldPen = dc_.SelectObject(&pen);
        dc_.MoveTo(x1, y1);
        dc_.LineTo(x2, y2);
        dc_.SelectObject(oldPen);
    }
    void DrawText(int x, int y, const std::string& text, SHColor color) override {
        dc_.SetTextColor(Col(color));
        dc_.SetBkMode(TRANSPARENT);
        dc_.TextOut(x, y, W(text));
    }
private:
    CDC& dc_;
    CRect rect_;
};

}  // namespace mfc
}  // namespace backend
}  // namespace shore