/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2020, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/

#include <time.h>
#include <iostream>
#include <chrono>
#include <ctime>

#include "EncoderLib/EncLibCommon.h"
#include "EncApp.h"
#include "Utilities/program_options_lite.h"


// begin rafael
int intvalor;
int iDF_SSE;
int iDF_SSE4;
int iDF_SSE8;
int iDF_SSE16;
int iDF_SSE32;
int iDF_SSE64;
int iDF_SSE16N;
int iDF_SAD;
int iDF_SAD4;
int iDF_SAD8;
int iDF_SAD16;
int iDF_SAD32;
int iDF_SAD64;
int iDF_SAD16N;
int iDF_SAD12;
int iDF_SAD24;
int iDF_SAD48;
int iDF_MRSAD;
int iDF_MRSAD2;
int iDF_MRSAD4;
int iDF_MRSAD8;
int iDF_MRSAD16;
int iDF_MRSAD32;
int iDF_MRSAD64;
int iDF_MRSAD16N;
int iDF_MRSAD12;
int iDF_MRSAD24;
int iDF_MRSAD48;
int iImpreciso;
int iTpsomador;
// end rafael

//! \ingroup EncoderApp
//! \{

static const uint32_t settingNameWidth = 66;
static const uint32_t settingHelpWidth = 84;
static const uint32_t settingValueWidth = 3;
// --------------------------------------------------------------------------------------------------------------------- //

//macro value printing function

#define PRINT_CONSTANT(NAME, NAME_WIDTH, VALUE_WIDTH) std::cout << std::setw(NAME_WIDTH) << #NAME << " = " << std::setw(VALUE_WIDTH) << NAME << std::endl;

static void printMacroSettings()
{
  if( g_verbosity >= DETAILS )
  {
    std::cout << "Non-environment-variable-controlled macros set as follows: \n" << std::endl;

    //------------------------------------------------

    //setting macros

    PRINT_CONSTANT( RExt__DECODER_DEBUG_BIT_STATISTICS,                         settingNameWidth, settingValueWidth );
    PRINT_CONSTANT( RExt__HIGH_BIT_DEPTH_SUPPORT,                               settingNameWidth, settingValueWidth );
    PRINT_CONSTANT( RExt__HIGH_PRECISION_FORWARD_TRANSFORM,                     settingNameWidth, settingValueWidth );
    PRINT_CONSTANT( ME_ENABLE_ROUNDING_OF_MVS,                                  settingNameWidth, settingValueWidth );

    //------------------------------------------------

    std::cout << std::endl;
  }
}

// ====================================================================================================================
// Main function
// ====================================================================================================================

int main(int argc, char* argv[])
{

// begin rafael
  iDF_SSE = 0;
  iDF_SSE4 = 0;
  iDF_SSE8 = 0;
  iDF_SSE16 = 0;
  iDF_SSE32 = 0;
  iDF_SSE64 = 0;
  iDF_SSE16N = 0;
  iDF_SAD = 0;
  iDF_SAD4 = 0;
  iDF_SAD8 = 0;
  iDF_SAD16 = 0;
  iDF_SAD32 = 0;
  iDF_SAD64 = 0;
  iDF_SAD16N = 0;
  iDF_SAD12 = 0;
  iDF_SAD24 = 0;
  iDF_SAD48 = 0;
  iDF_MRSAD = 0;
  iDF_MRSAD2 = 0;
  iDF_MRSAD4 = 0;
  iDF_MRSAD8 = 0;
  iDF_MRSAD16 = 0;
  iDF_MRSAD32 = 0;
  iDF_MRSAD64 = 0;
  iDF_MRSAD16N = 0;
  iDF_MRSAD12 = 0;
  iDF_MRSAD24 = 0;
  iDF_MRSAD48 = 0;

  // end rafael


  //rafael abetura de arquivos
//----------------------------------------
  string line;
  ifstream subtrator("subtrator.txt");
  if (subtrator.is_open())
  {
    while (getline(subtrator, line))
    {
      iTpsomador = atoi(line.c_str());
    }
    subtrator.close();
  }

  ifstream imprecisao("impreciso.txt");
  if (imprecisao.is_open())
  {
    while (getline(imprecisao, line))
    {
      iImpreciso = atoi(line.c_str());
    }
    imprecisao.close();
  }

  // print information

//abertura dos arquivos





//end rafael

  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "VVCSoftware: VTM Encoder Version %s ", VTM_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
#if ENABLE_SIMD_OPT
  std::string SIMD;
  df::program_options_lite::Options opts;
  opts.addOptions()
    ( "SIMD", SIMD, string( "" ), "" )
    ( "c", df::program_options_lite::parseConfigFile, "" );
  df::program_options_lite::SilentReporter err;
  df::program_options_lite::scanArgv( opts, argc, ( const char** ) argv, err );
  fprintf( stdout, "[SIMD=%s] ", read_x86_extension( SIMD ) );
#endif
#if ENABLE_TRACING
  fprintf( stdout, "[ENABLE_TRACING] " );
#endif
#if ENABLE_SPLIT_PARALLELISM
  fprintf( stdout, "[SPLIT_PARALLEL (%d jobs)]", PARL_SPLIT_MAX_NUM_JOBS );
#endif
#if ENABLE_SPLIT_PARALLELISM
  const char* waitPolicy = getenv( "OMP_WAIT_POLICY" );
  const char* maxThLim   = getenv( "OMP_THREAD_LIMIT" );
  fprintf( stdout, waitPolicy ? "[OMP: WAIT_POLICY=%s," : "[OMP: WAIT_POLICY=,", waitPolicy );
  fprintf( stdout, maxThLim   ? "THREAD_LIMIT=%s" : "THREAD_LIMIT=", maxThLim );
  fprintf( stdout, "]" );
#endif
  fprintf( stdout, "\n" );

  std::fstream bitstream;
  EncLibCommon encLibCommon;

  std::vector<EncApp*> pcEncApp(1);
  bool resized = false;
  int layerIdx = 0;

  initROM();
  TComHash::initBlockSizeToIndex();

  char** layerArgv = new char*[argc];

  do
  {
    pcEncApp[layerIdx] = new EncApp( bitstream, &encLibCommon );
    // create application encoder class per layer
    pcEncApp[layerIdx]->create();

    // parse configuration per layer
    try
    {
      int j = 0;
      for( int i = 0; i < argc; i++ )
      {
        if( argv[i][0] == '-' && argv[i][1] == 'l' )
        {
          if( argv[i][2] == std::to_string( layerIdx ).c_str()[0] )
          {
            layerArgv[j] = argv[i + 1];
            layerArgv[j + 1] = argv[i + 2];
            j += 2;
          }
          i += 2;
        }
        else
        {
          layerArgv[j] = argv[i];
          j++;
        }
      }

      if( !pcEncApp[layerIdx]->parseCfg( j, layerArgv ) )
      {
        pcEncApp[layerIdx]->destroy();
        return 1;
      }
    }
    catch( df::program_options_lite::ParseFailure &e )
    {
      std::cerr << "Error parsing option \"" << e.arg << "\" with argument \"" << e.val << "\"." << std::endl;
      return 1;
    }

    pcEncApp[layerIdx]->createLib( layerIdx );

    if( !resized )
    {
      pcEncApp.resize( pcEncApp[layerIdx]->getMaxLayers() );
      resized = true;
    }

    layerIdx++;
  } while( layerIdx < pcEncApp.size() );

  delete[] layerArgv;

#if JVET_Q0172_CHROMA_FORMAT_BITDEPTH_CONSTRAINT
  if (layerIdx > 1)
  {
    VPS* vps = pcEncApp[0]->getVPS();
    //check chroma format and bit-depth for dependent layers
    for (uint32_t i = 0; i < layerIdx; i++)
    {
      int curLayerChromaFormatIdc = pcEncApp[i]->getChromaFormatIDC();
      int curLayerBitDepth = pcEncApp[i]->getBitDepth();
      for (uint32_t j = 0; j < layerIdx; j++)
      {
        if (vps->getDirectRefLayerFlag(i, j))
        {
          int refLayerChromaFormatIdcInVPS = pcEncApp[j]->getChromaFormatIDC();
          CHECK(curLayerChromaFormatIdc != refLayerChromaFormatIdcInVPS, "The chroma formats of the current layer and the reference layer are different");
          int refLayerBitDepthInVPS = pcEncApp[j]->getBitDepth();
          CHECK(curLayerBitDepth != refLayerBitDepthInVPS, "The bit-depth of the current layer and the reference layer are different");
        }
      }
    }
  }
#endif

#if PRINT_MACRO_VALUES
  printMacroSettings();
#endif

  // starting time
  auto startTime  = std::chrono::steady_clock::now();
  std::time_t startTime2 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  fprintf(stdout, " started @ %s", std::ctime(&startTime2) );
  clock_t startClock = clock();

  // call encoding function per layer
  bool eos = false;

  while( !eos )
  {
    // read GOP
    bool keepLoop = true;
    while( keepLoop )
    {
      for( auto & encApp : pcEncApp )
      {
#ifndef _DEBUG
        try
        {
#endif
          keepLoop = encApp->encodePrep( eos );
#ifndef _DEBUG
        }
        catch( Exception &e )
        {
          std::cerr << e.what() << std::endl;
          return EXIT_FAILURE;
        }
        catch( const std::bad_alloc &e )
        {
          std::cout << "Memory allocation failed: " << e.what() << std::endl;
          return EXIT_FAILURE;
        }
#endif
      }
    }

    // encode GOP
    keepLoop = true;
    while( keepLoop )
    {
      for( auto & encApp : pcEncApp )
      {
#ifndef _DEBUG
        try
        {
#endif
          keepLoop = encApp->encode();
#ifndef _DEBUG
        }
        catch( Exception &e )
        {
          std::cerr << e.what() << std::endl;
          return EXIT_FAILURE;
        }
        catch( const std::bad_alloc &e )
        {
          std::cout << "Memory allocation failed: " << e.what() << std::endl;
          return EXIT_FAILURE;
        }
#endif
      }
    }
  }
  // ending time
  clock_t endClock = clock();
  auto endTime = std::chrono::steady_clock::now();
  std::time_t endTime2 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
#if JVET_O0756_CALCULATE_HDRMETRICS
  auto metricTime = pcEncApp[0]->getMetricTime();

  for( int layerIdx = 1; layerIdx < pcEncApp.size(); layerIdx++ )
  {
    metricTime += pcEncApp[layerIdx]->getMetricTime();
  }
  auto totalTime      = std::chrono::duration_cast<std::chrono::milliseconds>( endTime - startTime ).count();
  auto encTime        = std::chrono::duration_cast<std::chrono::milliseconds>( endTime - startTime - metricTime ).count();
  auto metricTimeuser = std::chrono::duration_cast<std::chrono::milliseconds>( metricTime ).count();
#else
  auto encTime = std::chrono::duration_cast<std::chrono::milliseconds>( endTime - startTime).count();
#endif

  for( auto & encApp : pcEncApp )
  {
    encApp->destroyLib();

    // destroy application encoder class per layer
    encApp->destroy();

    delete encApp;
  }

  // destroy ROM
  destroyROM();

  pcEncApp.clear();

  printf( "\n finished @ %s", std::ctime(&endTime2) );

#if JVET_O0756_CALCULATE_HDRMETRICS
  printf(" Encoding Time (Total Time): %12.3f ( %12.3f ) sec. [user] %12.3f ( %12.3f ) sec. [elapsed]\n",
         ((endClock - startClock) * 1.0 / CLOCKS_PER_SEC) - (metricTimeuser/1000.0),
         (endClock - startClock) * 1.0 / CLOCKS_PER_SEC,
         encTime / 1000.0,
         totalTime / 1000.0);
#else
  printf(" Total Time: %12.3f sec. [user] %12.3f sec. [elapsed]\n",
         (endClock - startClock) * 1.0 / CLOCKS_PER_SEC,
         encTime / 1000.0);
#endif

  return 0;
}

//! \}
