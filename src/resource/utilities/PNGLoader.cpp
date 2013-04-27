#include "src/resource/utilities/PNGLoader.hpp"

bool png_loader::loadPNG(char *name, int &outWidth, int &outHeight,
	bool &outHasAlpha, GLubyte **outData) {

    png_structp pngPtr;
    png_infop infoPtr;
    unsigned int sigRead = 0;
    int colorType, interlaceType;
    FILE *file; 


    if ((file = fopen(name, "rb")) == NULL) {

    	return false;
	}

    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (pngPtr == NULL) {

        fclose(file);
        return false;
    }

    infoPtr = png_create_info_struct(pngPtr);
    if (infoPtr == NULL) {

        fclose(file);
        png_destroy_read_struct(&pngPtr, png_infopp_NULL, png_infopp_NULL);
        return false;
    }

    if (setjmp(png_jmpbuf(pngPtr))) {

        png_destroy_read_struct(&pngPtr, &infoPtr, png_infopp_NULL);
        fclose(file);
        return false;
    }

    png_init_io(pngPtr, file);
    png_set_sig_bytes(pngPtr, sigRead);

    png_read_png(pngPtr, infoPtr,
    	PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND,
    	png_voidp_NULL);

    outWidth = infoPtr->width;
    outHeight = infoPtr->height;

    switch (infoPtr->color_type) {

        case PNG_COLOR_TYPE_RGBA: {

            outHasAlpha = true;
            break;
        }
        case PNG_COLOR_TYPE_RGB: {

            outHasAlpha = false;
            break;
        }
        default: {

        	//TODO: throw exeception
            std::cout << "Color type " << infoPtr->color_type <<
            	" not supported" << std::endl;

            png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
            fclose(file);
            return false;
        }
    }

    unsigned int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
    *outData = (unsigned char*) malloc(rowBytes*outHeight);
    png_bytepp rowPointers = png_get_rows(pngPtr, infoPtr);

    for (int i = 0; i < outHeight; i++) {

        memcpy(*outData + (rowBytes * (outHeight - 1 - i)),
        	rowPointers[i], rowBytes);
    }

    png_destroy_read_struct(&pngPtr, &infoPtr, png_infopp_NULL);
    fclose(file);

    return true;
}