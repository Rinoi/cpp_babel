#include	"Application.h"

int	main(int argc, char *argv[])
{
  Babel::Client::Application	app(argc, argv);

  return app.exec();
}
