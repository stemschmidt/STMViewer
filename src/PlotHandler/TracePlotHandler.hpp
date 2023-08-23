#ifndef _TRACEPLOTHANDLER_HPP
#define _TRACEPLOTHANDLER_HPP

#include <map>

#include "Plot.hpp"
#include "PlotHandlerBase.hpp"
#include "StlinkTraceDevice.hpp"
#include "TraceReader.hpp"
#include "spdlog/spdlog.h"

class TracePlotHandler : public PlotHandlerBase
{
   public:
	typedef struct
	{
		uint32_t coreFrequency;
		uint32_t tracePrescaler = 10;
		uint32_t maxPoints = 10000;
		uint32_t maxViewportPoints = 5000;
		int32_t triggerChannel = -1;
		double triggerLevel = 0.9;
	} Settings;

	TracePlotHandler(std::atomic<bool>& done, std::mutex* mtx, std::shared_ptr<spdlog::logger> logger);
	~TracePlotHandler();

	Settings getSettings() const;
	void setSettings(const Settings& settings);

	std::map<const char*, uint32_t> getTraceIndicators() const;

	std::string getLastReaderError() const;

	void setTriggerChannel(int32_t triggerChannel);
	int32_t getTriggerChannel() const;

	std::map<std::string, std::shared_ptr<Variable>> traceVars;

   private:
	void dataHandler();

   private:
	Settings traceSettings{};
	std::shared_ptr<StlinkTraceDevice> traceDevice;
	std::unique_ptr<TraceReader> traceReader;
	bool traceTriggered = false;
	static constexpr uint32_t channels = 10;
	double time = 0.0;
};

#endif