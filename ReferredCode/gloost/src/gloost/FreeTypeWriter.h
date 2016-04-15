
/*
                       ___                            __
                      /\_ \                          /\ \__
                   __ \//\ \     ___     ___     ____\ \  _\
                 /'_ `\ \ \ \   / __`\  / __`\  /  __\\ \ \/
                /\ \ \ \ \_\ \_/\ \ \ \/\ \ \ \/\__   \\ \ \_
                \ \____ \/\____\ \____/\ \____/\/\____/ \ \__\
                 \/___/\ \/____/\/___/  \/___/  \/___/   \/__/
                   /\____/
                   \_/__/

                   OpenGL framework for fast demo programming

                             http://www.gloost.org

    This file is part of the gloost framework. You can use it in parts or as
       whole under the terms of the GPL (http://www.gnu.org/licenses/#GPL).
*/



#ifndef H_GLOOST_FREETYPEWRITER
#define H_GLOOST_FREETYPEWRITER



// gloost system includes
#include <gloost/gloostConfig.h>
#include <gloost/gloostMath.h>


// cpp includes
#include <string>
#include <memory>
#include <map>


#define GLOOST_FREETYPEWRITER_ALIGN_LEFT   0
#define GLOOST_FREETYPEWRITER_ALIGN_RIGHT  1

#define GLOOST_FREETYPEWRITER_ALIGN_BOTTOM 0
#define GLOOST_FREETYPEWRITER_ALIGN_TOP    1

#define GLOOST_FREETYPEWRITER_ALIGN_CENTER 2



namespace gloost
{

  //  Writes Text on screen using ttf fonts (uses GNU's freetype)

class FreeTypeWriter
{
	public:


    /// monocrome pixel containing a luminance and an alpha value
    class MonocromPixel
    {
      public:

        MonocromPixel() {};
        MonocromPixel(float value): _luminance(value), _alpha(value) {};
        MonocromPixel(float luminance, float alpha): _luminance(luminance), _alpha(alpha) {};

        void  setLuminance(float luminance) {_luminance = luminance; }
        float getLuminance() const          { return _luminance; }
        void  setAlpha(float alpha)         {_alpha = alpha; }
        float getAlpha() const              { return _alpha; }

      private:

        float _luminance;
        float _alpha;
    };

#if 0
    // a pixel buffer consisting of
    class PixelBuffer
    {
      public:

       PixelBuffer(unsigned width, unsigned height):
         _width(width),
         _height(height),
         _pixels(width*height, MonocromPixel(0.5f, 0.5f))
       {

       }

       unsigned getWidth()  const { return _width; }
       unsigned getHeight() const { return _height; }

       std::vector<MonocromPixel>& getPixels() { return _pixels; }
       const std::vector<MonocromPixel>& getPixels() const { return _pixels; };

      private:

       unsigned _width;
       unsigned _height;
       std::vector<MonocromPixel> _pixels;
    };
#endif



	  /// stores the properties of a freetype glyph
	  struct glyphSpec
	  {
	    glyphSpec():
	      _leftOffset(0),
	      _topOffset(0),
	      _width(0),
	      _height(0),
	      _texcoords(0.0f, 0.0f, 0.0f, 0.0f)
	    {
	    }

	    glyphSpec(unsigned char index,
               int leftOffset, int topOffset,
               int width, int height)
	    {
	      _leftOffset = leftOffset;
	      _topOffset  = topOffset;
	      _width      = width;
	      _height     = height;
	    }

      unsigned char _index;
      int           _leftOffset;
      int           _topOffset;
      int           _width;
      int           _height;
      vec4          _texcoords;
	  };


    /// a std::shared_ptr of an ShaderProgram instance
    typedef std::shared_ptr<FreeTypeWriter>       shared_ptr;
    typedef std::shared_ptr<const FreeTypeWriter> const_shared_ptr;

    // class factory
    static shared_ptr create (const std::string& fontPath,
                              float              fontSize,
                              bool               antialiased = true,
                              unsigned           alignModeH = GLOOST_FREETYPEWRITER_ALIGN_LEFT,
                              float              charSpace  = 1.0f,
                              float              lineSpace  = 1.0f);

    // class constructor
    FreeTypeWriter(const std::string& fontPath,
                   float              fontSize,
                   bool               antialiased = true,
                   unsigned           alignModeH = GLOOST_FREETYPEWRITER_ALIGN_LEFT,
                   float              charSpace  = 1.0f,
                   float              lineSpace  = 1.0f);

    // class destructor
	  ~FreeTypeWriter();

	  // returns a container with the left and top bearings and horizontal and vertical size of each char
	  std::vector<glyphSpec>& getGlyphSpecs();
	  const std::vector<glyphSpec>& getGlyphSpecs() const;

	  // returns the gloostId of the generated atlas texture with the glyphes
    gloostId getFontAtlasTextureGid() const;

    // binds the font atlas and setups writing
    bool beginText();

    // ends the text writing
    void endText();

    // writes a line of text
    void writeLine(float x, float y, const std::string& text);
    void writeLine(float xOffset, const std::string& text);
    void writeLine(const std::string& text);

    // skips a line
    void nextLine();


    // returns the length of a line for current configuration
    float getLineLength(const std::string& text) const;

    // cuts a line, so it is not longer as maxPixelLength with the current font
    std::string cutLineToLength(const std::string& text, unsigned maxPixelLength) const;


    // sets the write position
    void setWritePos(const Point3& pos);
    void setWritePos(float x, float y);

    // returns the current writer position
    const Point3& getWritePos() const;

    // sets the horizontal align mode to GLOOST_FREETYPEWRITER_ALIGN_LEFT, GLOOST_FREETYPEWRITER_ALIGN_RIGHT or GLOOST_FREETYPEWRITER_ALIGN_CENTER
    void setAlignModeH(unsigned alignModeH);


    // returnt the fontsize
    float getFontSize() const;

    // sets the space between chars
    void setCharSpace(float charSpace);
    // returns the space between chars
    float getCharSpace() const;


    // sets the space between lines
    void setLineSpace (float lineDistance);
    // returns the space between lines
    float getLineSpace () const;
    // returns the height of a line (font height + line space)
    float getLineHeight() const;


    // sets the forced fixed Glyph
    void setForcedFixedWidth(float fixedWidth);

    // returns the forced fixed Glyph
    float getForcedFixedWidth() const;

    // inserts ...
    void insert_into_atlasComposeBuffer(unsigned char charIndex,
                                        std::vector<MonocromPixel>& monocromPixelBuffer,  unsigned bufferWidth, unsigned bufferHeight,
                                        const std::vector<MonocromPixel>& bufferToInsert, unsigned insertWidth, unsigned insertHeight,
                                        unsigned insertPosH, unsigned insertPosV);

	private:

   // setup
   std::string _fontPath;
   float       _fontSize;
   bool        _antialiased;

   // specs
   std::vector<glyphSpec> _glyphSpecs;

   //
   gloostId _glyphAtlasTextureGid;

   // writing
   gloost::Point3 _currentWritePosition;
   float          _charSpace;
   float          _lineHeight;
   float          _lineSpace;

   float          _forcedGlyphWidth;
   unsigned       _alignModeH;

   // write routine
   void write (const std::string& text);

};



} // namespace gloost


#endif // H_GLOOST_FREETYPEWRITER


