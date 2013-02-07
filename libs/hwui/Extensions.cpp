/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Debug.h"
#include "Extensions.h"

namespace android {

using namespace uirenderer;
ANDROID_SINGLETON_STATIC_INSTANCE(Extensions);

namespace uirenderer {

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////

// Debug
#if DEBUG_EXTENSIONS
    #define EXT_LOGD(...) ALOGD(__VA_ARGS__)
#else
    #define EXT_LOGD(...)
#endif

///////////////////////////////////////////////////////////////////////////////
// Constructors
///////////////////////////////////////////////////////////////////////////////

Extensions::Extensions(): Singleton<Extensions>() {
    const char* buffer = (const char*) glGetString(GL_EXTENSIONS);
    const char* current = buffer;
    const char* head = current;
    EXT_LOGD("Available GL extensions:");
    do {
        head = strchr(current, ' ');
        String8 s(current, head ? head - current : strlen(current));
        if (s.length()) {
            mExtensionList.add(s);
            EXT_LOGD("  %s", s.string());
        }
        current = head + 1;
    } while (head);

    mHasNPot = hasExtension("GL_OES_texture_npot");
    mHasFramebufferFetch = hasExtension("GL_NV_shader_framebuffer_fetch");
    mHasDiscardFramebuffer = hasExtension("GL_EXT_discard_framebuffer");
    mHasDebugMarker = hasExtension("GL_EXT_debug_marker");
    mHasDebugLabel = hasExtension("GL_EXT_debug_label");
    mHasTiledRendering = hasExtension("GL_QCOM_tiled_rendering");
    mHas1BitStencil = hasExtension("GL_OES_stencil1");
    mHas4BitStencil = hasExtension("GL_OES_stencil4");

    mExtensions = strdup(buffer);
}

Extensions::~Extensions() {
   free(mExtensions);
}

///////////////////////////////////////////////////////////////////////////////
// Methods
///////////////////////////////////////////////////////////////////////////////

bool Extensions::hasExtension(const char* extension) const {
   const String8 s(extension);
   return mExtensionList.indexOf(s) >= 0;
}

void Extensions::dump() const {
   ALOGD("Supported extensions:\n%s", mExtensions);
}

}; // namespace uirenderer
}; // namespace android
