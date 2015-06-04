#include "daisy/daisy.h"
// #include "kutility/kutility.h"

//using namespace kutility;

// using kutility::uchar;

//enum { NONE, DISPLAY, DISPLAY_UNNORM, SAVE_SINGLE, SAVE_ALL_ASCII, SAVE_ALL_BINARY, TIME_RUN, RANDOM_SAMPLE };

static int N=1000000;

int main( int argc, char **argv  )
{
   int counter=1;

   if(  argc == 1 || !strcmp("-h", argv[counter] ) || !strcmp("--help", argv[counter] ) )
   {
      display_help();
   }

   int w,h;
   uchar* im = NULL;
   int verbose_level=0;

   double opy = -1;
   double opx = -1;
   int opo =  0;

   int rad   = 15;
   int radq  =  3;
   int thq   =  8;
   int histq =  8;

   int nrm_type = NRM_PARTIAL;

   int orientation_resolution = 18;
   bool rotation_inv = false;

   char buffer[10];
   char* filename=NULL;

   int operation_mode=NONE;

   bool disable_interpolation = false;

   // Get command line options
   while( counter < argc )
   {
      if( !strcmp("-i", argv[counter] ) || !strcmp("--image", argv[counter]) )
      {
         filename = argv[++counter];
         // im = load_byte_image(filename,w,h);
         load_gray_image (filename, im, h, w);
         counter++;
         continue;
      }
      if( !strcmp("-p", argv[counter] ) || !strcmp("--param", argv[counter]) )
      {
         if( argc <= counter+4 ) error( "you must enter daisy params" );
         set_positive_integer( rad, argv[++counter], "rad");
         set_positive_integer( radq, argv[++counter], "radq");
         set_positive_integer( thq, argv[++counter],   "thq");
         set_positive_integer( histq, argv[++counter], "histq");
         counter++;
         continue;
      }
      if( !strcmp("-ri", argv[counter] ) || !strcmp("--rotation-inv", argv[counter]) )
      {
         if( argc <= counter+1 ) error( "you must enter orientation resolution" );
         set_positive_integer( orientation_resolution, argv[++counter], "orientation_resolution");
         rotation_inv = true;
         counter++;
         continue;
      }

      if( !strcmp("-d", argv[counter] ) || !strcmp("--display", argv[counter]) )
      {
         if( argc <= counter+3 ) error( "you must enter coordinates" );
         opy = atof( argv[++counter] );
         opx = atof( argv[++counter] );
         // set_positive_integer( opy, argv[++counter], "y");
         // set_positive_integer( opx, argv[++counter], "x");
         set_integer( opo, argv[++counter], "o");
         counter++;
         operation_mode = DISPLAY;
         continue;
      }
      if( !strcmp("-du", argv[counter] ) || !strcmp("--display-unnormalized", argv[counter]) )
      {
         if( argc <= counter+3 ) error( "you must enter coordinates" );
         opy = atof( argv[++counter] );
         opx = atof( argv[++counter] );
         // set_positive_integer( opy, argv[++counter], "y");
         // set_positive_integer( opx, argv[++counter], "x");
         set_integer( opo, argv[++counter], "o");
         counter++;
         operation_mode = DISPLAY_UNNORM;
         continue;
      }

      if( !strcmp("-s", argv[counter] ) || !strcmp("--save", argv[counter]) )
      {
         if( argc <= counter+3 ) error( "you must enter coordinates" );
         opy = atof( argv[++counter] );
         opx = atof( argv[++counter] );
         // set_positive_integer( opy, argv[++counter], "y");
         // set_positive_integer( opx, argv[++counter], "x");
         set_integer( opo, argv[++counter], "o");
         counter++;
         operation_mode = SAVE_SINGLE;
         continue;
      }
      if( !strcmp("-nt", argv[counter] ) )
      {
         if( argc <= counter+1 ) error( "you must enter normalization type" );
         set_integer( nrm_type, argv[++counter], "nrm_type");
         counter++;
         continue;
      }

      if( !strcmp("-sa", argv[counter] ) || !strcmp("--save-all-ascii", argv[counter]) )
      {
         operation_mode = SAVE_ALL_ASCII;
         counter++;
         continue;
      }
      if( !strcmp("-sb", argv[counter] ) || !strcmp("--save-all-binary", argv[counter]) )
      {
         operation_mode = SAVE_ALL_BINARY;
         counter++;
         continue;
      }
      if( !strcmp("-tr", argv[counter] ) )
      {
         operation_mode = TIME_RUN;
         counter++;
         continue;
      }
      if( !strcmp("-rs", argv[counter] ) )
      {
         operation_mode = RANDOM_SAMPLE;
         counter++;
         continue;
      }
      if( !strcmp("-di", argv[counter] ) || !strcmp("--disable-interpolation", argv[counter]) )
      {
         counter++;
         disable_interpolation = true;
         continue;
      }
      if( !strcmp("-v", argv[counter] ) || !strcmp("--verbose", argv[counter]) )
      {
         counter++;
         verbose_level = 1;
         continue;
      }
      if( !strcmp("-vv", argv[counter] ) )
      {
         counter++;
         verbose_level = 2;
         continue;
      }
      if( !strcmp("-vvv", argv[counter] ) )
      {
         counter++;
         verbose_level = 3;
         continue;
      }
      if( !strcmp("-vvvv", argv[counter] ) )
      {
         counter++;
         verbose_level = 4;
         continue;
      }
      warning("unknown option");
      cout<<"option : "<<argv[counter]<<endl;
      counter ++;
      exit(1);
   }

   if( filename == NULL )
   {
      error("you haven't specified the filename mate.");
   }

   daisy* desc = new daisy();

   if( disable_interpolation ) desc->disable_interpolation();

   desc->set_image(im,h,w);
   deallocate(im);
   desc->verbose( verbose_level );
   desc->set_parameters(rad, radq, thq, histq);
   if( nrm_type == 0 ) desc->set_normalization( NRM_PARTIAL );
   if( nrm_type == 1 ) desc->set_normalization( NRM_FULL );
   if( nrm_type == 2 ) desc->set_normalization( NRM_SIFT );

// !! this part is optional. You don't need to set the workspace memory
   int ws = desc->compute_workspace_memory();
   float* workspace = new float[ ws ];
   desc->set_workspace_memory( workspace, ws);
// !! this part is optional. You don't need to set the workspace memory

   desc->initialize_single_descriptor_mode();

// !! this is work in progress. do not enable!
//    if( rotation_inv ) desc->rotation_invariant(orientation_resolution, rotation_inv);
// !! this is work in progress. do not enable!


// !! this part is optional. You don't need to set the descriptor memory
   // int ds = desc->compute_descriptor_memory();
   // float* descriptor_mem = new float[ds];
   // desc->set_descriptor_memory( descriptor_mem, ds );
// !! this part is optional. You don't need to set the descriptor memory

   string fname;
   float* thor = new float[desc->descriptor_size()];

   // i don't set the histogram that are outside the image to 0 for performance
   // issues. you should do it yourself.
   memset(thor, 0, sizeof(float)*desc->descriptor_size() );

   time_t st,en;
   double yy, xx;
   int ori;
   string outname = filename;
   int rand_samples[N*2];
   for( int i=0; i<N;i++) {
      rand_samples[2*i]=rand()%(h-1)+0.4;
      rand_samples[2*i+1]=rand()%(w-1)+0.4;
   }
   time(&st);

   desc->get_descriptor(opy,opx,opo,thor);
   display(thor, desc->grid_point_number(), histq, 0, 0 );
   break;

   delete desc;
   // delete []workspace;
   // delete []descriptor_mem;

   return 0;
}
