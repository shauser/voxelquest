
const int MAX_KEYS = 256;


enum eProgramState {
	E_PS_MENU,
	E_PS_IN_GAME,
	E_PS_SIZE
};

enum eProgramAction {
	E_PA_QUIT,
	E_PA_TOGGLE_FULLSCREEN,
	E_PA_REFRESH,
	E_PA_SIZE
};

enum E_TEX_TYPE {
    E_TEX_TYPE_NOISE
};

enum E_RENDER_METHODS {
    E_RENDER_NONE,
    E_RENDER_VOL,
    E_RENDER_LENGTH
};

enum E_STATES {
    E_STATE_INIT_LAUNCH,
    E_STATE_INIT_BEG,
    E_STATE_INIT_END,
    E_STATE_CREATESIMPLEXNOISE_LAUNCH,
    E_STATE_CREATESIMPLEXNOISE_BEG,
    E_STATE_CREATESIMPLEXNOISE_END,
    E_STATE_NEIGHBORSREADY_LAUNCH,
    E_STATE_NEIGHBORSREADY_BEG,
    E_STATE_NEIGHBORSREADY_END,
    E_STATE_COPYTOTEXTURE_LAUNCH,
    E_STATE_COPYTOTEXTURE_BEG,
    E_STATE_COPYTOTEXTURE_END,

    E_STATE_GENERATEVOLUME_LAUNCH,
    E_STATE_GENERATEVOLUME_BEG,
    E_STATE_GENERATEVOLUME_END,

    E_STATE_WAIT,
    E_STATE_LENGTH

};

enum E_FILL_STATE {
    E_FILL_STATE_EMPTY,
    E_FILL_STATE_PARTIAL,
    E_FILL_STATE_FULL,
};

enum E_OBJ {
    E_OBJ_CAMERA,
    E_OBJ_LIGHT,
    E_OBJ_LENGTH
};


//#define DEBUG_MODE 

//const static int MAX_THREADS = 8; 
