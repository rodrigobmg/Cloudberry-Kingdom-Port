﻿#include <CorePS3.h>

#include <Architecture/Scheduler.h>
#include <Audio/MediaPlayer.h>
#include <Audio/PS3/mscommon.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstdarg>
#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Input/GamePad.h>
#include <Input/Keyboard.h>
#include <list>
#include <Utility/Error.h>
#include <Utility/Limits.h>
#include <Utility/Log.h>

#include <cell/l10n.h>
#include <cell/sysmodule.h>
#include <netex/libnetctl.h>
#include <np.h>
#include <np/drm.h>
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>
#include <sys/ppu_thread.h>
#include <sys/process.h>
#include <sys/spu_initialize.h>
#include <sysutil/sysutil_bgmplayback.h>
#include <sysutil/sysutil_gamecontent.h>
#include <sysutil/sysutil_msgdialog.h>
#include <sysutil/sysutil_savedata.h>

#include <Utility/ConsoleInformation.h>

SYS_PROCESS_PARAM ( 1000, 0x80000 )

// Passphrase and signature from PSN Server Management Tools.
static const SceNpCommunicationId s_npCommunicationId = {
    {'N', 'P', 'W', 'R', '0', '4', '4', '1', '3'},
    '\0',
    0,
    0
};

/***
SceNpCommunicationPassphrase

416ea7dc6715f7fb874be27c584df3efc5757062bc2b3992c74b7d42ee450914995edf73efa5e5e7f6bc4b1687be6a0cf40fab915d7657bd0afe59b8decf07cc7ec6b7d6be22489a874eb7efda3b65d46577a7ce2a423176f8ad38a0ead670ded8c70edb8d4543c0b30e295a769efad5b76e4d00e40e2d93dbca69688ea1f097
***/

static const SceNpCommunicationPassphrase s_npCommunicationPassphrase = {
    {
        0x41,0x6e,0xa7,0xdc,0x67,0x15,0xf7,0xfb,
        0x87,0x4b,0xe2,0x7c,0x58,0x4d,0xf3,0xef,
        0xc5,0x75,0x70,0x62,0xbc,0x2b,0x39,0x92,
        0xc7,0x4b,0x7d,0x42,0xee,0x45,0x09,0x14,
        0x99,0x5e,0xdf,0x73,0xef,0xa5,0xe5,0xe7,
        0xf6,0xbc,0x4b,0x16,0x87,0xbe,0x6a,0x0c,
        0xf4,0x0f,0xab,0x91,0x5d,0x76,0x57,0xbd,
        0x0a,0xfe,0x59,0xb8,0xde,0xcf,0x07,0xcc,
        0x7e,0xc6,0xb7,0xd6,0xbe,0x22,0x48,0x9a,
        0x87,0x4e,0xb7,0xef,0xda,0x3b,0x65,0xd4,
        0x65,0x77,0xa7,0xce,0x2a,0x42,0x31,0x76,
        0xf8,0xad,0x38,0xa0,0xea,0xd6,0x70,0xde,
        0xd8,0xc7,0x0e,0xdb,0x8d,0x45,0x43,0xc0,
        0xb3,0x0e,0x29,0x5a,0x76,0x9e,0xfa,0xd5,
        0xb7,0x6e,0x4d,0x00,0xe4,0x0e,0x2d,0x93,
        0xdb,0xca,0x69,0x68,0x8e,0xa1,0xf0,0x97
    }
};

/***
SceNpCommunicationSignature

b9dde13b0100000000000000a2f2d66966b3f8d64f9c7dc9fa81e8fdd335cfa7b4b0b1dca063cf38f7dc3a46bad2dbf90dbd293f146165764419818cf74d9612680ec39bd3dbc02c3f87dc36a5721baea8ead5085ba7c89e77d29577ad157cd610c1f5b380783070b51dbeb37eec58387f707d89879fac90358847dbe9a912929ad92a92c01f8bfc1d788e5aeea145a44892f8cb5d198d2bbf54ec783952deee
***/

static const SceNpCommunicationSignature s_npCommunicationSignature = {
    {
        0xb9,0xdd,0xe1,0x3b,0x01,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0xa2,0xf2,0xd6,0x69,
        0x66,0xb3,0xf8,0xd6,0x4f,0x9c,0x7d,0xc9,
        0xfa,0x81,0xe8,0xfd,0xd3,0x35,0xcf,0xa7,
        0xb4,0xb0,0xb1,0xdc,0xa0,0x63,0xcf,0x38,
        0xf7,0xdc,0x3a,0x46,0xba,0xd2,0xdb,0xf9,
        0x0d,0xbd,0x29,0x3f,0x14,0x61,0x65,0x76,
        0x44,0x19,0x81,0x8c,0xf7,0x4d,0x96,0x12,
        0x68,0x0e,0xc3,0x9b,0xd3,0xdb,0xc0,0x2c,
        0x3f,0x87,0xdc,0x36,0xa5,0x72,0x1b,0xae,
        0xa8,0xea,0xd5,0x08,0x5b,0xa7,0xc8,0x9e,
        0x77,0xd2,0x95,0x77,0xad,0x15,0x7c,0xd6,
        0x10,0xc1,0xf5,0xb3,0x80,0x78,0x30,0x70,
        0xb5,0x1d,0xbe,0xb3,0x7e,0xec,0x58,0x38,
        0x7f,0x70,0x7d,0x89,0x87,0x9f,0xac,0x90,
        0x35,0x88,0x47,0xdb,0xe9,0xa9,0x12,0x92,
        0x9a,0xd9,0x2a,0x92,0xc0,0x1f,0x8b,0xfc,
        0x1d,0x78,0x8e,0x5a,0xee,0xa1,0x45,0xa4,
        0x48,0x92,0xf8,0xcb,0x5d,0x19,0x8d,0x2b,
        0xbf,0x54,0xec,0x78,0x39,0x52,0xde,0xee
    }
};

// Drm key for checking file access.
static const SceNpDrmKey s_npDrmKey = {
	{ 0xb1, 0x28, 0xb8, 0x67, 0x56, 0xd4, 0x68, 0x2b, 0x16, 0x18, 0x33, 0x8b, 0x49, 0x66, 0x44, 0xd9 }
};

// Private.
CorePS3::CorePS3( const CorePS3 &other ) :
	game_( other.game_ ),
	qd_( other.qd_ ),
	content_( other.content_ )
{

}

// Private.
CorePS3 &CorePS3::operator = ( const CorePS3 &rhs )
{
	return *this;
}

// Abstract error checking.
#define CELL_ERR_CHECK( code, msg )					   \
{													   \
	int ret = ( code );								   \
	switch( ret )									   \
	{												   \
	case CELL_OK:									   \
		break;										   \
													   \
	case CELL_SYSMODULE_ERROR_DUPLICATED:			   \
		break;										   \
													   \
	case CELL_SYSMODULE_ERROR_UNKNOWN:				   \
	case CELL_SYSMODULE_ERROR_FATAL:				   \
		LOG_WRITE( msg );							   \
		LOG_WRITE( "!! EXITING PROGRAM !!\n" );		   \
		exit( 1 );									   \
	}												   \
}

// Override music volume when BGM is playing. Defined in MediaPlayerPS3.cpp.
extern void SetBGMOverride( bool override );

// Is the system menu open? Defined in ConsoleInformationPS3.cpp.
extern bool GLOBAL_SYSTEM_MENU_OPEN;

// Pause and resume the background job system.  Defined in SchedulerPS3.cpp.
extern void PauseScheduler();
extern void ResumeScheduler();

// Kick off saves on exit to make sure we save everything. Defined in EzStorage.cpp.
extern void SaveAllOnExit();

static void SystemCallback( const uint64_t status, const uint64_t param, void *userdata )
{
	( void )param;
	( void )userdata;

	switch( status )
	{
	case CELL_SYSUTIL_REQUEST_EXITGAME:
		//SaveAllOnExit();
		glFinish();
		CORE.Exit();
		break;
	case CELL_SYSUTIL_DRAWING_BEGIN:
	case CELL_SYSUTIL_DRAWING_END:
		break;
	case CELL_SYSUTIL_SYSTEM_MENU_OPEN:
		GLOBAL_SYSTEM_MENU_OPEN = true;
		PauseScheduler();
		break;
	case CELL_SYSUTIL_SYSTEM_MENU_CLOSE:
		GLOBAL_SYSTEM_MENU_OPEN = false;
		ResumeScheduler();
		break;
	case CELL_SYSUTIL_NET_CTL_NETSTART_FINISHED:
		{
			CellNetCtlNetStartDialogResult result;
			result.size = sizeof( result );
			result.result = 0;

			int ret = cellNetCtlNetStartDialogUnloadAsync( &result );
			if( ret < 0 )
				LOG_WRITE( "Failed to cellNetCtlNetStartDialogUnloadAsync: 0x%x\n", ret );
			else
				LOG_WRITE( "cellNetCtlNetStartDialogUnloadAsync result = 0x%x\n", ret );
		}
		break;
	case CELL_SYSUTIL_BGMPLAYBACK_PLAY:
		SetBGMOverride( true );
		break;
	case CELL_SYSUTIL_BGMPLAYBACK_STOP:
		SetBGMOverride( false );
		break;
	default:
		LOG_WRITE( "Unknown callback status: 0x%llx\n", status );
	}
}

// FIXME: EXTERNALS FOR SHARING INFORMATION GLOBALLY!

std::string PS3_PATH_PREFIX;

int GLOBAL_WIDTH;
int GLOBAL_HEIGHT;

// Preallocate all memory used by video player.  Defined in VideoPlayerPS3.cpp.
extern void ReserveVideoPlayerMemory();

extern void KillVideoPlayer();

// Wait for save and load operations to finish.  Defined in EzStorage.cpp.
extern void WaitForSaveLoad();

CorePS3::CorePS3( GameLoop &game ) :
	running_( false ),
	game_( game ),
	qd_( 0 ),
	content_( 0 ),
	scheduler_( 0 )
{
	sys_spu_initialize( 6, 1 );

	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_GCM_SYS ), "Failed to load GCM_SYS\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_FS ), "Failed to load FS\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_USBD ), "Failed to load USBD\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_IO ), "Failed to load IO\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_SYSUTIL_GAME ), "Failed to load IO\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_SYSUTIL_NP ), "Failed to load NP\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_SYSUTIL_LICENSEAREA ), "Failed to load License Area\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_NETCTL ), "Failed to load NETCTL\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_L10N ), "Failed to load L10N\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_PAMF ), "Failed to load PAMF\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_SAIL ), "Failed to load SAIL\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_AVCONF_EXT ), "Failed to load AVCONF\n" );

	LoadModules();

	unsigned int type;
	unsigned int attributes;
	CellGameContentSize size;
	char dirName[ CELL_GAME_PATH_MAX ];
	cellGameBootCheck( &type, &attributes, &size, dirName );
	LOG_WRITE( "cellGameBootCheck: type = %d, attributes = 0x%x, dirName = %s\n", type, attributes, dirName );
	LOG_WRITE( "CellGameContentSize: hddFreeSizeKB = %d KB, sizeKB = %d KB, sysSizeKB = %d KB\n", size.hddFreeSizeKB, size.sizeKB, size.sysSizeKB );

	char contentInfoPath[ CELL_GAME_PATH_MAX ];
	char usrdirPath[ CELL_GAME_PATH_MAX ];

	cellGameContentPermit( contentInfoPath, usrdirPath );
	PS3_PATH_PREFIX = std::string( usrdirPath ) + "/";
	// To test an hdd game in release mode with the debugger we need to tell it about the
	// game code.  Also the files should be pre-installed on the disk.
	// PS3_PATH_PREFIX = "/dev_hdd0/game/NPEB01312/USRDIR/"; // SCEE
	// PS3_PATH_PREFIX = "/dev_hdd0/game/NPUB31177/USRDIR/"; // SCEA
	// PS3_PATH_PREFIX = "/app_home/";
	LOG_WRITE( "Running in %s\nContent dir %s\n", dirName, usrdirPath );
#ifdef DEBUG
	PS3_PATH_PREFIX = "/app_home/";
#endif

	// Audio system uses system callback 0.
	int ret = cellSysutilRegisterCallback( 1, SystemCallback, NULL );
	if( ret != CELL_OK )
	{
		LOG_WRITE( "Failed to register system callback: error=0x%x\n", ret );
		exit( 1 );
	}

	PSGLinitOptions initOpts = {
		enable: PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS | PSGL_INIT_HOST_MEMORY_SIZE,
		maxSPUs: 1,
		initializeSPUs: false,
		persistentMemorySize: 0,
		transientMemorySize: 0,
		errorConsole: 0,
		fifoSize: 0,
		hostMemorySize: 64 * 1024 * 1024
	};

	psglInit( &initOpts );

	// Pick video resolution.
	struct dstResType { int w, h; uint32_t resId; uint32_t aspect; };
	const dstResType dstRes[] = {
		{ 720, 480, CELL_VIDEO_OUT_RESOLUTION_480, CELL_VIDEO_OUT_ASPECT_AUTO },
		{ 720, 576, CELL_VIDEO_OUT_RESOLUTION_576, CELL_VIDEO_OUT_ASPECT_AUTO },
		//{ 720, 480, CELL_VIDEO_OUT_RESOLUTION_480, CELL_VIDEO_OUT_ASPECT_4_3 },
		//{ 720, 480, CELL_VIDEO_OUT_RESOLUTION_480, CELL_VIDEO_OUT_ASPECT_16_9 },
		//{ 720, 576, CELL_VIDEO_OUT_RESOLUTION_576, CELL_VIDEO_OUT_ASPECT_4_3 },
		//{ 720, 576, CELL_VIDEO_OUT_RESOLUTION_576, CELL_VIDEO_OUT_ASPECT_16_9 },
		{ 1280, 720, CELL_VIDEO_OUT_RESOLUTION_720, CELL_VIDEO_OUT_ASPECT_AUTO },
		{ 1280, 1080, CELL_VIDEO_OUT_RESOLUTION_1080, CELL_VIDEO_OUT_ASPECT_AUTO },
	};
	const int numDstRes = 4;

	PSGLdeviceParameters parameters;
	memset( &parameters, 0, sizeof( parameters ) );
	parameters.enable = PSGL_DEVICE_PARAMETERS_COLOR_FORMAT | PSGL_DEVICE_PARAMETERS_DEPTH_FORMAT
				| PSGL_DEVICE_PARAMETERS_MULTISAMPLING_MODE;
//				| PSGL_DEVICE_PARAMETERS_RESC_RATIO_MODE,
	parameters.colorFormat = GL_ARGB_SCE;
	parameters.depthFormat = GL_NONE;
	parameters.multisamplingMode = GL_MULTISAMPLING_NONE_SCE;
//		rescRatioMode: RESC_RATIO_MODE_LETTERBOX,

	// Pick best resolution.
	for( int i = numDstRes - 1; i >= 0; --i )
	{
		if( cellVideoOutGetResolutionAvailability( CELL_VIDEO_OUT_PRIMARY,
			dstRes[ i ].resId, dstRes[ i ].aspect, 0 ) )
		{
			LOG_WRITE( "Best supported resolution is %dx%d\n", dstRes[ i ].w, dstRes[ i ].h );

			switch( dstRes[ i ].resId )
			{
			case CELL_VIDEO_OUT_RESOLUTION_480:
			case CELL_VIDEO_OUT_RESOLUTION_576:
				parameters.enable |= PSGL_DEVICE_PARAMETERS_RESC_RATIO_MODE;
				parameters.rescRatioMode = RESC_RATIO_MODE_LETTERBOX;

				parameters.enable |= PSGL_DEVICE_PARAMETERS_WIDTH_HEIGHT;
				parameters.width = dstRes[ i ].w;
				parameters.height = dstRes[ i ].h;

				parameters.enable |= PSGL_DEVICE_PARAMETERS_RESC_RENDER_WIDTH_HEIGHT;
				parameters.renderWidth = dstRes[ i ].w;
				parameters.renderHeight = dstRes[ i ].h;

				parameters.multisamplingMode = GL_MULTISAMPLING_2X_DIAGONAL_CENTERED_SCE;
				break;
			case CELL_VIDEO_OUT_RESOLUTION_1080:
			case CELL_VIDEO_OUT_RESOLUTION_720:
				parameters.enable |= PSGL_DEVICE_PARAMETERS_WIDTH_HEIGHT;
				parameters.width = dstRes[ i ].w;
				parameters.height = dstRes[ i ].h;
				break;
			}

			break;
		}
	}

	static PSGLdevice *device = NULL;
	device = psglCreateDeviceExtended( &parameters );
	/*device = psglCreateDeviceAuto( GL_ARGB_SCE, GL_NONE,
		GL_MULTISAMPLING_NONE_SCE );*/

	if( !device )
	{
		LOG_WRITE( "Failed to create device\n" );
		exit( 1 );
	}

	GLuint width, height;
	psglGetDeviceDimensions( device, &width, &height );

	GLOBAL_WIDTH = width;
	GLOBAL_HEIGHT = height;

	LOG_WRITE( "Initializing device, resolution %d x %d\n", width, height );

	GLfloat aspect = psglGetDeviceAspectRatio( device );
	LOG_WRITE( "Aspect ratio %f\n", aspect );

	PSGLcontext *context = psglCreateContext();
	if( !context )
	{
		LOG_WRITE( "Failed to create context\n" );
		exit( -1 );
	}

	psglMakeCurrent( context, device );
	
	psglResetCurrentContext();

#ifdef DEBUG
	cgGLSetDebugMode( GL_TRUE );
#else
	cgGLSetDebugMode( GL_FALSE );
#endif

	glViewport( 0, 0, width, height );
	glScissor( 0, 0, width, height );
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	/*glClearDepthf( 1.f );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );*/

	glDisable( GL_CULL_FACE );
	glEnable( GL_VSYNC_SCE );

	glEnable( GL_BLEND );
	glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );

	glDisable( GL_DEPTH_TEST );
	
	cgGLEnableProfile( cgGLGetLatestProfile( CG_GL_VERTEX ) );
	cgGLEnableProfile( cgGLGetLatestProfile( CG_GL_FRAGMENT ) );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	psglSwap();

	ReserveVideoPlayerMemory();

	scheduler_ = new Scheduler;

	content_ = new Wad( PS3_PATH_PREFIX + "ContentPS3/" );

	qd_ = new QuadDrawer;

	td_ = new TextDrawer;

	GamePad::Initialize();
	MediaPlayer::Initialize();
}

CorePS3::~CorePS3()
{
	GamePad::Shutdown();

	delete td_;

	delete qd_;

	delete content_;

	delete scheduler_;

	// Need to shut down media player last as scheduler could still play a song.
	MediaPlayer::Shutdown();
	
	UnloadModules();

	cellSysmoduleUnloadModule( CELL_SYSMODULE_SYSUTIL_LICENSEAREA );
	cellSysmoduleUnloadModule( CELL_SYSMODULE_SYSUTIL_NP );
}

static SceNpTrophyContext TrophyContext;
static SceNpTrophyHandle TrophyHandle;
static bool ContextRegistered;
extern std::list< ErrorType > GLOBAL_ERROR_QUEUE;

bool GetTrophyContext( SceNpTrophyContext &context, SceNpTrophyHandle &handle )
{
	if( !ContextRegistered )
		return false;

	context = TrophyContext;
	handle = TrophyHandle;

	return true;
}

void ForceGetTrophyContext( SceNpTrophyContext &context, SceNpTrophyHandle &handle )
{
	context = TrophyContext;
	handle = TrophyHandle;
}

int TrophyStatusCallback( SceNpTrophyContext context, SceNpTrophyStatus status, int completed, int total, void *arg )
{
	int ret = 0;

	switch( status )
	{
	case SCE_NP_TROPHY_STATUS_NOT_INSTALLED:
		LOG_WRITE( "Trophy configuration not installed.\n" );
		break;
	case SCE_NP_TROPHY_STATUS_DATA_CORRUPT:
		LOG_WRITE( "Trophy data is corrupt.\n" );
		break;
	case SCE_NP_TROPHY_STATUS_INSTALLED:
		LOG_WRITE( "Trophy configuration has been installed.\n" );
		break;
	case SCE_NP_TROPHY_STATUS_REQUIRES_UPDATE:
		LOG_WRITE( "Trophy configuration requires update.\n" );
		break;
	case SCE_NP_TROPHY_STATUS_CHANGES_DETECTED:
		LOG_WRITE( "Trophy changes detected.\n" );
		break;
	case SCE_NP_TROPHY_STATUS_UNKNOWN:
		LOG_WRITE( "Trophy status unknown.\n" );
		break;
	default:
		LOG_WRITE( "Trophy status: %d\n", status );
		break;
	}

	return ret;
}

// Stuff to localize the register trophy message.
static std::string WstringToUtf8( const std::wstring& str )
{
	char utf8[ 512 ];
	size_t inSize = str.size();
	size_t outSize = sizeof( utf8 );
	if( l10n_convert_str( l10n_get_converter( L10N_UTF16, L10N_UTF8 ), str.c_str(), &inSize, utf8, &outSize ) != ConversionOK )
		return "";

	return std::string( utf8, utf8 + outSize );
}

static std::wstring Format( const wchar_t *format, ... )
{
	wchar_t buffer[512];

	va_list args;
	va_start( args, format );
	vswprintf( buffer, sizeof( buffer ) / sizeof( wchar_t ), format, args );
	va_end( args );

	return std::wstring( buffer );
}

bool gTrophyContextRegistered = true;

// Space needed for trophy, 
//extern uint64_t RequiredTrophySpace;

void RegisterTrophyContextThread( uint64_t context )
{
	ContextRegistered = false;

	// Register trophy.
	int ret = sceNpTrophyRegisterContext( TrophyContext, TrophyHandle, TrophyStatusCallback, NULL,
		SCE_NP_TROPHY_OPTIONS_REGISTER_CONTEXT_SHOW_ERROR_EXIT );
	if( ret < 0 )
	{
		LOG_WRITE( "Couldn't register trophy context: 0x%x\n", ret );
		ContextRegistered = false;

		/*if( SCE_NP_TROPHY_ERROR_INSUFFICIENT_DISK_SPACE == ret )
		{
			uint64_t requiredTrophySpace;
			ret = sceNpTrophyGetRequiredDiskSpace( TrophyContext, TrophyHandle, &requiredTrophySpace, 0 );
			if( ret == 0 )
			{
				std::string errorMsg = WstringToUtf8( Format( L"There is not enough free space on the system storage to register Trophy information.\nPlease quit the game and free %d KB.", requiredTrophySpace / 1024 ) );

				ConsoleLanguage language = GetConsoleLanguage();
				switch ( language )
				{
					case ConsoleLanguage_JAPANESE:
						errorMsg = WstringToUtf8( Format( L"トロフィー情報を登録するにはシステムストレージに十分な空き容量がありません。ゲームを終了し %d を確保してください。", requiredTrophySpace / 1024 ) );
						break;
					case ConsoleLanguage_FRENCH:
						errorMsg = WstringToUtf8( Format( L"Espace insuffisant sur le stockage système pour enregistrer les information de trophées. Veuillez quitter le jeu et libérer %d KB.", requiredTrophySpace / 1024 ) );
						break;
					case ConsoleLanguage_GERMAN:
						errorMsg = WstringToUtf8( Format( L"Es ist nicht genügend freier Speicherplatz im Systemspeicher vorhanden, um Trophäen-Informationen einzutragen. Bitte beende das Spiel und schaffe %d KB freien Speicher.", requiredTrophySpace / 1024 ) );
						break;
					case ConsoleLanguage_ITALIAN:
						errorMsg = WstringToUtf8( Format( L"Non c'è sufficiente spazio libero nello spazio di archiviazione del sistema per registrare le informazioni sui trofei. Uscire dal gioco e liberare %d KB.", requiredTrophySpace / 1024 ) );
						break;
					case ConsoleLanguage_SPANISH:
						errorMsg = WstringToUtf8( Format( L"No hay suficiente espacio libre en el almacenamiento del sistema para registrar la información de trofeos. Sal del juego y libera %d KB.", requiredTrophySpace / 1024 ) );
						break;
					case ConsoleLanguage_CHINESE:
						errorMsg = WstringToUtf8( Format( L"主机存储器剩余空间不足, 无法保存Trophy（奖杯）信息。请退出游戏并释放至少 %d KB剩余空间。", requiredTrophySpace / 1024 ) );
						break;
					case ConsoleLanguage_KOREAN:
						errorMsg = WstringToUtf8( Format( L"트로피 정보를 기록하는데 필요한 본체 스토리지의 디스크 공간이 부족합니다. 게임을 종료하신 후, %d KB의 공간을 비우십시오.", requiredTrophySpace / 1024 ) );
						break;
					case ConsoleLanguage_PORTUGUESE:
						errorMsg = WstringToUtf8( Format( L"Não há espaço suficiente no armazenamento do sistema para registrar as informações de Troféu. Por favor saia do jogo e libere %d KB.", requiredTrophySpace / 1024 ) );
						break;
					case ConsoleLanguage_RUSSIAN:
						errorMsg = WstringToUtf8( Format( L"Недостаточно места на системном накопителе, чтобы зарегистрировать информацию о призах. Пожалуйста, выйдите из игры и очистите %d Кбайт.", requiredTrophySpace / 1024 ) );
						break;
					
					case ConsoleLanguage_DUTCH:
					case ConsoleLanguage_TAIWANESE:
					case ConsoleLanguage_ENGLISH:
					default:
						break;
				}

				DisplayError( ErrorType( errorMsg, NULL, ErrorType::NONE, NULL, true ) );
			}
			else
				DisplayError( ErrorType( ret, NULL, ErrorType::NONE, NULL, true ) );
		}*/
	}
	else
	{
		LOG_WRITE( "Trophy context registered.\n", ret );
		ContextRegistered = true;
	}

	gTrophyContextRegistered = true;
	LOG_WRITE( "Trophy configuration done.\n" );

	sys_ppu_thread_exit( 0 );
}

static SceNpId NPId;
static int ScoreTitleContext = 0;
static bool NPIdObtained = false;

bool GetNPScoreContext( int &id )
{
	if( !NPIdObtained )
		return false;

	id = ScoreTitleContext;

	return true;
}

bool IsNPAvailable()
{
	return NPIdObtained;
}

/*void CreateScoreContext( uint64_t context )
{
	//NPIdObtained = false;

	int ret = sceNpScoreCreateTitleCtx( s_npCommunicationId, s_npCommunicationPassphrase, userNpId );
	if( ret > 0 )
	{
		NPId = ret; 
		NPIdObtained = true;
		return;
	}

	switch( ret )
	{
	}

	sys_ppu_thread_exit( 0 );
}*/

void ConnectToNPThread( uint64_t context )
{
	int ret = sceNpManagerGetNpId( &NPId );
	switch( ret )
	{
	case SCE_NP_ERROR_NOT_INITIALIZED:
	case SCE_NP_ERROR_INVALID_ARGUMENT:
	case SCE_NP_ERROR_INVALID_STATE:
	case SCE_NP_ERROR_OFFLINE:
		sys_ppu_thread_exit( 0 );
		return;
		break;

	case 0:
		break;
	}

	ret = sceNpScoreCreateTitleCtx( &s_npCommunicationId, &s_npCommunicationPassphrase, &NPId );
	if( ret > 0 )
	{
		ScoreTitleContext = ret;
		NPIdObtained = true;
	}
	else
		LOG_WRITE( "Coldn't get score title context: 0x%x\n", ret );

	sys_ppu_thread_exit( 0 );
}

void ConnectToNP()
{
	if( NPIdObtained )
	{
		LOG_WRITE( "Tried to connect to NP multiple times!\n" );
		return;
	}

	LOG_WRITE( "Connecting to NP!\n" );

	// Kick off NP connection.
	sys_ppu_thread_t tid;
	int ret = sys_ppu_thread_create( &tid, ConnectToNPThread, 0,
		1001, 16 * 1024, 0, "ConnectToNP" );
	if( ret != 0 )
		LOG_WRITE( "Failed to start ConnectToNP: 0x%x\n", ret );
}

ErrorType GLOBAL_NP_DISCONNECT_MESSAGE;

void DisconnectFromNP()
{
	DisplayError( GLOBAL_NP_DISCONNECT_MESSAGE );
	LOG_WRITE( "Disconnecting from NP\n" );

	if( NPIdObtained )
	{
		sceNpScoreDestroyTitleCtx( ScoreTitleContext );
	}

	NPIdObtained = false;
}

void NPManagerCallback( int event, int result, void *arg )
{
	LOG_WRITE( "NP EVENT: %d\tRESULT: %d\n", event, result );
	switch( event )
	{
	case SCE_NP_MANAGER_STATUS_OFFLINE:
		DisconnectFromNP();
		break;
	case SCE_NP_MANAGER_STATUS_GETTING_TICKET:
		break;
	case SCE_NP_MANAGER_STATUS_GETTING_PROFILE:
		break;
	case SCE_NP_MANAGER_STATUS_LOGGING_IN:
		break;
	case SCE_NP_MANAGER_STATUS_ONLINE:
		{
			int id;
			if( !GetNPScoreContext( id ) )
				ConnectToNP();
		}
		break;
	}
}

static bool ErrorDialogOpen = false;
static ErrorType CurrentError( 0 );

void ErrorDialogCallback( int buttonType, void *userData )
{
	ErrorType::CompleteCallback complete = CurrentError.GetComplete();

	switch( buttonType )
	{
	case CELL_MSGDIALOG_BUTTON_YES:
		if( complete )
			complete( true );
		break;
	case CELL_MSGDIALOG_BUTTON_NO:
		if( complete )
			complete( false );
		break;

	default:
		if( complete )
			complete( false );
		break;
	}

	ErrorDialogOpen = false;
}

#define NP_POOL_SIZE (128 * 1024)
static uint8_t NPPool[ NP_POOL_SIZE ];

void DebugFrame(float r, float g, float b)
{
	static int count = 0;
	
	/*glEnable(GL_SCISSOR_TEST);
	glViewport(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);

	for( int i = 0; i < 2; ++i )
	{
		glScissor(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);
		glClearColor( r, g, b, 1 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		int j = 0;
		for( int i = 31; i >= 0; --i)
		{
			glScissor(j, 0, 32, 128);

			if( count & (1 << i) )
				glClearColor( 1, 1, 1, 1 );
			else
				glClearColor( 0, 0, 0, 1 );

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			j += 33;
		}

		psglSwap();
	}*/
	
	++count;
	//glDisable(GL_SCISSOR_TEST);
}

void NPDRMInvalidCompleteCallback( bool yes )
{
	glFinish();
	CORE.Exit();
}

void CheckNPDRMFileThread( uint64_t context )
{
	std::string file_path = PS3_PATH_PREFIX + "UNLOCK.EDAT";
	int ret = sceNpDrmIsAvailable2( &s_npDrmKey, file_path.c_str() );
	
	if( ret == 0 )
	{
		// Good to go.
	}
	/*else
	{
		// Error!
		DisplayError( ErrorType( ret, NPDRMInvalidCompleteCallback, ErrorType::NONE, NULL, true ) );
	}*/

	sys_ppu_thread_exit( 0 );
}

int CorePS3::Run()
{
	running_ = true;

	// Initialize NP.
	int ret = sceNpInit( NP_POOL_SIZE, NPPool );
	if( ret < 0 )
		LOG_WRITE( "Failed to initialize NP: 0x%x\n", ret );

	sceNpManagerRegisterCallback( NPManagerCallback, NULL );

	// Initialize NP score system.
	ret = sceNpScoreInit();
	if( ret < 0 )
		LOG_WRITE( "Failed to initialize score system: 0x%x\n", ret );

	// Initialize trophy system.
	ret = sceNpTrophyInit( NULL, 0, SYS_MEMORY_CONTAINER_ID_INVALID, 0 );
	if( ret < 0 )
		LOG_WRITE( "Failed to initialize trophy system: 0x%x\n", ret );

	int npState;
	sceNpManagerGetStatus( &npState );

	// Initialize our own connection to NP if the console is already connected.
	if( npState == SCE_NP_MANAGER_STATUS_ONLINE )
		ConnectToNP();

	// The communication ID comes from PSN Server Management Tools on PSN.
	TrophyContext = SCE_NP_TROPHY_INVALID_CONTEXT;
	ret = sceNpTrophyCreateContext( &TrophyContext, &s_npCommunicationId, &s_npCommunicationSignature, 0 );
	if( ret < 0 )
		LOG_WRITE( "Can't create trophy context: 0x%x\n", ret );

	TrophyHandle = SCE_NP_TROPHY_INVALID_HANDLE;
	ret = sceNpTrophyCreateHandle( &TrophyHandle );
	if( ret < 0 )
		LOG_WRITE( "Couldn't create trophy handle: 0x%x\n", ret );

	// Kick off trophy synchronization.
	/*sys_ppu_thread_t tid;
	ret = sys_ppu_thread_create( &tid, RegisterTrophyContextThread, 0,
		1001, 16 * 1024, 0, "RegisterTrophyContextThread" );
	if( ret != 0 )
		LOG_WRITE( "Failed to start RegisterTrophyContextThread: 0x%x\n", ret );
	*/

	ret = cellNetCtlInit();
	if( ret < 0 )
		LOG_WRITE( "Failed to cellNetCtlInit: 0x%x\n", ret );

	// Enable BGM playback.
	ret = cellSysutilEnableBgmPlayback();
	if( ret < 0 )
		LOG_WRITE( "Failed to allow BGM playback: 0x%x\n", ret );

	//DisplayError( ErrorType( 0x8002a1a4 ) );
	game_.Initialize();

	// Check game NPDRM.
	sys_ppu_thread_t tid;
	ret = sys_ppu_thread_create( &tid, CheckNPDRMFileThread,
		0, 1001, 16 * 1024, 0, "CheckNPDRMFileThread" );

	while( running_ )
	{		
		GamePad::Update();
		Keyboard::Update();

		if( ErrorDialogOpen )
		{
			if( CurrentError.GetAutoClose() )
			{
				if( CurrentError.GetAutoClose()() )
					cellMsgDialogClose( 0.f );
			}

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			int ret = cellSysutilCheckCallback();
			if( ret )
				LOG_WRITE( "cellSysutilChecCallback() = 0x%x\n", ret );

			psglSwap();
			continue;
		}

		if( GLOBAL_ERROR_QUEUE.size() > 0 )
		{
			CurrentError = GLOBAL_ERROR_QUEUE.front();
			GLOBAL_ERROR_QUEUE.pop_front();

			int ret = 0;
			switch( CurrentError.GetMessageType() )
			{
			case ErrorType::CODE:
				ret = cellMsgDialogOpenErrorCode( CurrentError.GetCode(), ErrorDialogCallback, NULL, NULL );
				break;
			case ErrorType::STRING:
				{
					unsigned int type = CurrentError.IsFatal() ? CELL_MSGDIALOG_TYPE_SE_TYPE_ERROR : CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL;
					switch( CurrentError.GetInputType() )
					{
					case ErrorType::DEFAULT:
						break;
					case ErrorType::YESNO:
						type |= CELL_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO;
						break;
					case ErrorType::OK:
						type |= CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK;
						break;
					case ErrorType::NONE:
						type |= CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON;
						break;
					}

					ret = cellMsgDialogOpen2( type, CurrentError.GetMessage().c_str(), ErrorDialogCallback, NULL, NULL );
				}
				break;
			}
			if( ret == 0 )
			{
				ErrorDialogOpen = true;
				continue;
			}
		}

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		scheduler_->MainThread();

		game_.Update();

		qd_->Flush();

		int ret = cellSysutilCheckCallback();
		if( ret )
			LOG_WRITE( "cellSysutilChecCallback() = 0x%x\n", ret );

		psglSwap();
	}

	// Close the dialog box if it is still open.
	/*if( ErrorDialogOpen ) 
		cellMsgDialogClose( 0.0f );

	while( ErrorDialogOpen )
	{
		int ret = cellSysutilCheckCallback();
		if( ret )
			LOG_WRITE( "cellSysutilChecCallback() = 0x%x\n", ret );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		psglSwap();
	}*/

	if( TrophyHandle != SCE_NP_TROPHY_INVALID_HANDLE )
		sceNpTrophyAbortHandle(TrophyHandle);

	KillVideoPlayer();
	WaitForSaveLoad();

	while( !gTrophyContextRegistered )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		int ret = cellSysutilCheckCallback();
		if( ret )
			LOG_WRITE( "cellSysutilChecCallback() = 0x%x\n", ret );

		psglSwap();

		sys_ppu_thread_yield();
	}

	return 0;
}

void CorePS3::Exit()
{
	running_ = false;
}
