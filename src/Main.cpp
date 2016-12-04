#include <Communicating/Communicator.h>
#include <Communicating/Console.h>
#include <Communicating/SocketSrv.h>
#include <Communicating/StatementFormat.h>
#include <Acquiring/RemoteVideoStreamAcquirer.h>
#include <Performing/Performer.h>
#include <Performing/OpenCVPerformer.h>
#include <System/Configurator.h>
#include <iostream>

int main(int argc, char* argv[])
{
	communicating::Communicator communicator;
	// Communicator dependencies injection
	communicating::StatementFormat statementFormat;
	//communicating::Console console(statementFormat);
	communicating::SocketSrv socketSrv(statementFormat);
	//communicator.addImpl(console);
	communicator.addImpl(socketSrv);

	acquiring::RemoteVideoStreamAcquirer videoStreamAcquirer;

	performing::OpenCVPerformer cvPerformer;
	// Performer dependency injection
	performing::Performer performer(cvPerformer);

	communicator.start();
	videoStreamAcquirer.start();
	performer.start();

	//Test the proptree
	/*bool test = (
		Configurator::getInstance().get<std::string>("StreamLocation") ==
		"undefined"
	);

	std::cout << "StreamLocation = " << test << std::endl;
	std::cout.flush();*/

	performer.join();
	videoStreamAcquirer.join();
	communicator.join();

	return 0;
}
