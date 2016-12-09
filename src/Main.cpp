#include <Communicating/Communicator.h>
#include <Communicating/Console.h>
#include <Communicating/SocketSrv.h>
#include <Communicating/StatementFormat.h>
#include <Acquiring/RemoteVideoStreamAcquirer.h>
#include <Acquiring/LocalVideoStreamAcquirer.h>
#include <Performing/Performer.h>
#include <Performing/OpenCVPerformer.h>
#include <System/Configurator.h>
#include <iostream>

using namespace acquiring;
using namespace communicating;
using namespace performing;
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Communicator communicator;
		// Communicator dependencies injection
		StatementFormat statementFormat;
		//communicating::Console console(statementFormat);
		SocketSrv socketSrv(statementFormat);
		//communicator.addImpl(console);
		communicator.addImpl(socketSrv);

		//acquiring::RemoteVideoStreamAcquirer videoStreamAcquirer;
		const char* videoPath = R"(C:\Users\MrG0z\Documents\Visual Studio 2015\Projects\HumanDetector\Release\pedestrian.avi)";
		LocalVideoStreamAcquirer videoStreamAcquirer(videoPath);

		OpenCVPerformer cvPerformer;
		// Performer dependency injection
		Performer performer(cvPerformer, videoStreamAcquirer);

		communicator.start();
		videoStreamAcquirer.start();
		performer.start();

		performer.join();
		videoStreamAcquirer.join();
		communicator.join();

	} catch (const DeviceNotFound& e) {
		cerr << e.what() << endl;
	} catch (const FileNotFound& e) {
		cerr << e.what() << endl;
	}

	return 0;
}
