//@+leo-ver=4-thin
//@+node:leonardoce.20090622083507.3:@thin forthconsole.c
//@@language c

#include <stdio.h>
#include <string.h>
#include "quattro_parser.h"
#include "quattro_vm.h"
#include "utils.h"

int main(int argc, char **argv) {
  ForthVm *vm = NULL;
  char kernelFile[1024];
  char startupFile[1024];
  int i;

  strcpy(kernelFile, "full.4th");

  //@  <<argomenti cmd>>
  //@+node:leonardoce.20090622083507.12:<<argomenti cmd>>
  startupFile[0]='\x0';

  for(i=1;i<argc;i++) {
      if(strcmp(argv[i],"--image")==0) {
          InputStream *in = InputStream_NewForFile(argv[i+1]);
          vm=ForthVm_NewFromFile(in);
          InputStream_Delete(in);
          i++;
      } else if(strcmp(argv[i],"--kernel")==0) {
          strcpy(kernelFile, argv[i+1]);
          i++;
      } else if(strcmp(argv[i],"--exec")==0) {
          strcpy(startupFile, argv[i+1]);
      } else if(strcmp(argv[i],"--help")==0 || strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-?")==0) {
          printf("%s\n", LEOFORTH_VERSION);
          printf("Use: %s [opts]\n\n", argv[0]);
          printf("Options: \n");
          printf("--kernel <nomefile>   Use the specified kernel\n");
          printf("--image <nomefile>    Load an image\n");
          printf("--exec <nomefile>     Execute a file\n");
          printf("--help                This help message\n");
          printf("-?\n");
          printf("-h\n");
          printf("\n");
          return(0);
      }

  }
  //@-node:leonardoce.20090622083507.12:<<argomenti cmd>>
  //@nl

  if(vm==NULL) {
    vm=ForthVm_New();
  }

  ForthStream *fstr;

  //@  <<kernel>>
  //@+node:leonardoce.20090630084051.24:<<kernel>>
  fstr = ForthStream_NewForFile(kernelFile);
  ForthVm_SetParser(vm, fstr);
  ForthVm_Feed(vm);
  ForthStream_Delete(fstr);
  //@nonl
  //@-node:leonardoce.20090630084051.24:<<kernel>>
  //@nl
  //@  <<informazioni benvenuto>>
  //@+node:leonardoce.20090629082550.233:<<informazioni benvenuto>>
  printf("using kernel %s\n", kernelFile);
  //@-node:leonardoce.20090629082550.233:<<informazioni benvenuto>>
  //@nl
  //@  <<file startup>>
  //@+node:leonardoce.20090630084051.23:<<file startup>>
  if(strlen(startupFile)!=0) {
    printf("loading %s\n", startupFile);

    fstr = ForthStream_NewForFile(startupFile);
    ForthVm_SetParser(vm, fstr);
    ForthVm_Feed(vm);
    ForthStream_Delete(fstr);  
  }
  //@nonl
  //@-node:leonardoce.20090630084051.23:<<file startup>>
  //@nl

  fstr = ForthStream_NewForBuffer("<line>", "internal-repl");
  ForthVm_SetParser(vm, fstr);

  printf("\n\n");

  while(TRUE) {
    vm->exitFlag=0;
    ForthVm_Feed(vm);
    ForthVm_Output(vm, " ok\n");
    fflush(stdout);
  }

  ForthStream_Delete(fstr);
  ForthVm_Delete(vm);

  return 0;
}
//@-node:leonardoce.20090622083507.3:@thin forthconsole.c
//@-leo
