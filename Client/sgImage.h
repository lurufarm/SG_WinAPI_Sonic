#pragma once
#include "sgResource.h"

namespace sg
{

	class Image : public Resource
	{
	public:
		static Image* Create(const std::wstring& name, UINT width, UINT height);

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};

}
