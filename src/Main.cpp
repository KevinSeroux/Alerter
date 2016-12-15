#include <Communicating/Communicator.h>
#include <Communicating/Console.h>
#include <Communicating/SocketSrv.h>
#include <Communicating/StatementFormat.h>
#include <Acquiring/LocalVideoStreamAcquirer.h>
#include <Performing/Performer.h>
#include <Performing/OpenCVPerformer.h>
#include <System/Configurator.h>
#include <boost/di.hpp>
#include <iostream>

using namespace acquiring;
using namespace communicating;
using namespace performing;
using namespace std;
using namespace boost;

class App
{
public:
	App(Communicator& com, Performer& perf, VideoStreamAcquirer& stream) :
		m_com(com), m_perf(perf), m_stream(stream) {}

	void setFile(const char* file)
	{
		Configurator::getInstance().put("StreamLocation", file);
	}

	void run()
	{
		m_com.start();
		m_stream.start();
		m_perf.start();

		m_perf.join();
		m_stream.join();
		m_com.join();
	}

private:
	Communicator& m_com;
	Performer& m_perf;
	VideoStreamAcquirer& m_stream;
};

int main(int argc, char* argv[])
{
	auto injector = di::make_injector(
		di::bind<VideoStreamAcquirer>().to<LocalVideoStreamAcquirer>(),
		di::bind<PerformerInt>().to<OpenCVPerformer>(),
		di::bind<IOInt>().to<SocketSrv>(),
		di::bind<LanguageInt>().to<StatementFormat>()
	);

	App app = injector.create<App>();
	app.setFile("samples/pedestrian.avi");
	app.run();

	return 0;
}
