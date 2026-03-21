#include "resource_preview_gif_texture.h"

#include "../core/gif_texture.h"
#include "../core/gif_reader.h"

#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/file_access.hpp>

namespace godot {
	void ResourcePreviewGIFTexture::_bind_methods() {
		
	}

	bool ResourcePreviewGIFTexture::_handles(const String& p_type) const {
		return p_type == "GIFTexture";
	}

	Ref<Texture2D> ResourcePreviewGIFTexture::_generate(const Ref<Resource>& p_resource, const Vector2i& p_size, const Dictionary& p_metadata) const {
		Ref<GIFTexture> gif = p_resource;
		if (gif.is_null() || gif->get_frame_count() == 0) {
			return Ref<Texture2D>();
		}

		Ref<ImageTexture> frame_texture = gif->get_frame_texture(0);
		if (frame_texture.is_null()) {
			return Ref<Texture2D>();
		}

		Ref<Image> img = frame_texture->get_image();
		if (img.is_null()) {
			return Ref<Texture2D>();
		}

		Vector2i img_size = img->get_size();
		if (img_size.x > p_size.x || img_size.y > p_size.y) {
			float scale = MIN((float)p_size.x / img_size.x, (float)p_size.y / img_size.y);
			img = img->duplicate();
			img->resize(MAX(1, (int)(img_size.x * scale)), MAX(1, (int)(img_size.y * scale)), Image::INTERPOLATE_BILINEAR);
		}

		return ImageTexture::create_from_image(img);
	}

	Ref<Texture2D> ResourcePreviewGIFTexture::_generate_from_path(const String& p_path, const Vector2i& p_size, const Dictionary& p_metadata) const {
		return Ref<Texture2D>();
	}

	bool ResourcePreviewGIFTexture::_generate_small_preview_automatically() const {
		return false;
	}

	bool ResourcePreviewGIFTexture::_can_generate_small_preview() const {
		return false;
	}
}
