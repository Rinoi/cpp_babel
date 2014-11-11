#include "PluginLoaderWindows.hh"


namespace Babel
{
  namespace Server
  {
    namespace Plugin
    {

		AServerPlugin *
		PluginLoaderWindows::Load(const std::string &name)
		{
			std::vector<wchar_t> buf(MultiByteToWideChar(CP_ACP, 0, name.c_str(), name.size() + 1, 0, 0));
			MultiByteToWideChar(CP_ACP, 0, name.c_str(), name.size() + 1, &buf[0], buf.size());
			std::wstring winString(&buf[0]);
			winString += L".dll";

			HMODULE pluginLibrary = LoadLibrary(winString.c_str());
			if (pluginLibrary == 0) {
				std::cerr << GetLastError() << std::endl;
				std::cerr << "pluginLibrary == 0" << std::endl;
				return 0;
			}

			getPluginFuncPtr getPlugin = (getPluginFuncPtr)(GetProcAddress(pluginLibrary, "getPlugin"));
			if (getPlugin == 0) {
				std::cerr << GetLastError() << std::endl;
				std::cerr << "failed to find getPlugin function" << std::endl;
				return 0;
			}
			return getPlugin(this->_server);
		}
	}
  }
}
