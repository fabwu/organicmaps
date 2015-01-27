#pragma once

#include "../geometry/rect2d.hpp"

#include "../coding/file_writer.hpp"

#include "../std/vector.hpp"
#include "../std/string.hpp"


class FeatureBuilder1;

namespace feature
{
  struct GenerateInfo;

  bool GenerateFeatures(GenerateInfo & info, string const & nodeStorage, string const & osmFileName);

  // Writes features to dat file.
  class FeaturesCollector
  {
    char m_writeBuffer[48000];
    size_t m_writePosition = 0;
    uint32_t m_baseOffset = 0;

  protected:
    FileWriter m_datFile;
    m2::RectD m_bounds;

  private:
    void Write(char const * src, size_t size);
    void FlushBuffer();

  protected:
    static uint32_t GetFileSize(FileWriter const & f);

    /// @return feature offset in the file, which is used as an ID later
    uint32_t WriteFeatureBase(vector<char> const & bytes, FeatureBuilder1 const & fb);

    void Flush();

  public:
    FeaturesCollector(string const & fName);
    ~FeaturesCollector();

    void operator() (FeatureBuilder1 const & f);
  };
}
