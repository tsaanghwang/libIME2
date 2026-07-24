#ifndef IME_COMPOSITION_SEGMENT_STRIP_H
#define IME_COMPOSITION_SEGMENT_STRIP_H

#include <algorithm>
#include <string>
#include <vector>
#include <windows.h>

namespace Ime {

struct CompositionCodePointSpan {
    int utf16Start;
    int utf16Length;
};

struct CompositionSegmentItem {
    int start;
    int end;
    std::wstring code;
    std::wstring text;
    bool active;
};

inline std::vector<CompositionCodePointSpan> compositionCodePointSpans(const std::wstring& text) {
    std::vector<CompositionCodePointSpan> spans;
    for(int i = 0; i < static_cast<int>(text.length());) {
        int length = 1;
        if(IS_HIGH_SURROGATE(text[i]) && i + 1 < static_cast<int>(text.length())
            && IS_LOW_SURROGATE(text[i + 1])) {
            length = 2;
        }
        spans.push_back({i, length});
        i += length;
    }
    return spans;
}

inline void normalizeCompositionSegmentRange(
    int codePointCount, int& activeStart, int& activeEnd) {
    activeStart = (std::max)(0, (std::min)(activeStart, codePointCount));
    activeEnd = (std::max)(activeStart, (std::min)(activeEnd, codePointCount));
}

} // namespace Ime

#endif
