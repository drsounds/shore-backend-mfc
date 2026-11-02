#pragma once

#include <memory>
#include <shore/backend.h>

namespace shore {
namespace backend {
namespace mfc {

std::unique_ptr<SHBackend> CreateBackend();

}  // namespace mfc
}  // namespace backend
}  // namespace shore
