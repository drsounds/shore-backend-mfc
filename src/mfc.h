#pragma once

#include <afxwin.h>
#include <stdexcept>
#include <string>
#include <shore/types.h>

namespace shore {
namespace backend {
namespace mfc {

inline CString W(const std::string& s) {
    if (s.empty()) return CString();
    int length = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
    if (length <= 0) throw std::runtime_error("MFC failed to convert UTF-8 text");
    CStringW result;
    if (!MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, result.GetBuffer(length), length)) {
        result.ReleaseBuffer(0);
        throw std::runtime_error("MFC failed to convert UTF-8 text");
    }
    result.ReleaseBuffer(length - 1);
    return result;
}
inline COLORREF Col(SHColor color) { return RGB(color.r, color.g, color.b); }

}  // namespace mfc
}  // namespace backend
}  // namespace shore