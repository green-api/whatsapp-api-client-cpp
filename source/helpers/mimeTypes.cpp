#include "../../../whatsapp-api-client-cpp/include/helpers/mimeTypes.hpp"

namespace greenapi
{
	std::string getMimeTypes(const std::string& extension)
	{
		auto it = mimeTypes.find(extension);
		if (it != mimeTypes.end()) {
			return it->second;
		}
		else {
			return "application/octet-stream";
		}
	}

}// namespace greenapi