#ifndef __ALE_C_WRAPPER_H__
#define __ALE_C_WRAPPER_H__

// Declare var for __declspec(dllexport)
#define EXPORT __declspec(dllexport)

#include <ale_interface.hpp>

extern "C" {
  // Declares int rgb_palette[256]
  EXPORT ALEInterface *ALE_new() { return new ALEInterface(); }
  EXPORT void ALE_del(ALEInterface *ale){ delete ale; }
  EXPORT const char *getString(ALEInterface *ale, const char *key){ return ale->getString(key).c_str(); }
  EXPORT int getInt(ALEInterface *ale, const char *key) { return ale->getInt(key); }
  EXPORT bool getBool(ALEInterface *ale, const char *key){ return ale->getBool(key); }
  EXPORT float getFloat(ALEInterface *ale, const char *key){ return ale->getFloat(key); }
  EXPORT void setString(ALEInterface *ale, const char *key, const char *value){ ale->setString(key, value); }
  EXPORT void setInt(ALEInterface *ale, const char *key, int value){ ale->setInt(key, value); }
  EXPORT void setBool(ALEInterface *ale, const char *key, bool value){ ale->setBool(key, value); }
  EXPORT void setFloat(ALEInterface *ale, const char *key, float value){ ale->setFloat(key, value); }
  EXPORT void loadROM(ALEInterface *ale, const char *rom_file){ ale->loadROM(rom_file); }
  EXPORT int act(ALEInterface *ale, int action){ return ale->act((Action)action); }
  EXPORT bool game_over(ALEInterface *ale){ return ale->game_over(); }
  EXPORT void reset_game(ALEInterface *ale){ ale->reset_game(); }
  EXPORT void getLegalActionSet(ALEInterface *ale, int *actions){
    ActionVect action_vect = ale->getLegalActionSet();
    for(unsigned int i = 0;i < ale->getLegalActionSet().size();i++){
      actions[i] = action_vect[i];
    }
  }
  EXPORT int getLegalActionSize(ALEInterface *ale){ return ale->getLegalActionSet().size(); }
  EXPORT void getMinimalActionSet(ALEInterface *ale, int *actions){
    ActionVect action_vect = ale->getMinimalActionSet();
    for(unsigned int i = 0;i < ale->getMinimalActionSet().size();i++){
      actions[i] = action_vect[i];
    }
  }
  EXPORT int getMinimalActionSize(ALEInterface *ale){ return ale->getMinimalActionSet().size(); }
  EXPORT int getFrameNumber(ALEInterface *ale){ return ale->getFrameNumber(); }
  EXPORT int lives(ALEInterface *ale){ return ale->lives(); }
  EXPORT int getEpisodeFrameNumber(ALEInterface *ale){ return ale->getEpisodeFrameNumber(); }
  EXPORT void getScreen(ALEInterface *ale, unsigned char *screen_data){
    int w = ale->getScreen().width();
    int h = ale->getScreen().height();
    pixel_t *ale_screen_data = (pixel_t *)ale->getScreen().getArray();
    memcpy(screen_data,ale_screen_data,w*h*sizeof(pixel_t));
  }
  EXPORT void getRAM(ALEInterface *ale, unsigned char *ram){
    unsigned char *ale_ram = ale->getRAM().array();
    int size = ale->getRAM().size();
    memcpy(ram,ale_ram,size*sizeof(unsigned char));
  }
  EXPORT int getRAMSize(ALEInterface *ale){ return ale->getRAM().size(); }
  EXPORT int getScreenWidth(ALEInterface *ale){ return ale->getScreen().width(); }
  EXPORT int getScreenHeight(ALEInterface *ale){ return ale->getScreen().height(); }

  EXPORT void getScreenRGB(ALEInterface *ale, unsigned char *output_buffer){
    size_t w = ale->getScreen().width();
    size_t h = ale->getScreen().height();
    size_t screen_size = w*h;
    pixel_t *ale_screen_data = ale->getScreen().getArray();

    ale->theOSystem->colourPalette().applyPaletteRGB(output_buffer, ale_screen_data, screen_size );
  }

  EXPORT void getScreenGrayscale(ALEInterface *ale, unsigned char *output_buffer){
    size_t w = ale->getScreen().width();
    size_t h = ale->getScreen().height();
    size_t screen_size = w*h;
    pixel_t *ale_screen_data = ale->getScreen().getArray();

    ale->theOSystem->colourPalette().applyPaletteGrayscale(output_buffer, ale_screen_data, screen_size);
  }

  EXPORT void saveState(ALEInterface *ale){ ale->saveState(); }
  EXPORT void loadState(ALEInterface *ale){ ale->loadState(); }
  EXPORT ALEState* cloneState(ALEInterface *ale){ return new ALEState(ale->cloneState()); }
  EXPORT void restoreState(ALEInterface *ale, ALEState* state){ ale->restoreState(*state); }
  EXPORT ALEState* cloneSystemState(ALEInterface *ale){ return new ALEState(ale->cloneSystemState()); }
  EXPORT void restoreSystemState(ALEInterface *ale, ALEState* state){ ale->restoreSystemState(*state); }
  EXPORT void deleteState(ALEState* state){ delete state; }
  EXPORT void saveScreenPNG(ALEInterface *ale,const char *filename){ale->saveScreenPNG(filename);}

  // Encodes the state as a raw bytestream. This may have multiple '\0' characters
  // and thus should not be treated as a C string. Use encodeStateLen to find the length
  // of the buffer to pass in, or it will be overrun as this simply memcpys bytes into the buffer.
  EXPORT void encodeState(ALEState *state, char *buf, int buf_len);
  EXPORT int encodeStateLen(ALEState *state);
  EXPORT ALEState *decodeState(const char *serialized, int len);
}

#endif
