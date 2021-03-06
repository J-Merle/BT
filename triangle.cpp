#include "vulkan/vulkan.h"
#include "vulkan/vulkan_core.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_vulkan.h"

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <cstring>
class HelloTriangleApplication {

  public:
    void run() {
      initWindow();
      initVulkan();
      mainLoop();
      cleanup();
    }

  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    VkInstance instance;
    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

#ifdef NDEBUG
    static constexpr bool enableValidationLayers = false;
#else
    static constexpr bool enableValidationLayers = true;
#endif

    void initWindow() {
      window = SDL_CreateWindow("Triangle", SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_VULKAN|SDL_WINDOW_SHOWN);
      renderer = SDL_CreateRenderer(window, -1, 0);
    }

    void initVulkan() {
      createInstance();
    }

    void mainLoop() {
      while(1) {
        if(SDL_PollEvent(&event)) {
          if(event.type == SDL_QUIT) {
            break;
          }
        } 
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
      }
    }

    void cleanup() {
      vkDestroyInstance(instance, nullptr);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
    }

    void createInstance() {
      if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
      }

      VkApplicationInfo appInfo = {};
      appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
      appInfo.pApplicationName = "Blanco Tower";
      appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
      appInfo.pEngineName = "No Engine";
      appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
      appInfo.apiVersion = VK_API_VERSION_1_2;

      VkInstanceCreateInfo createInfo = {};
      createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
      createInfo.pApplicationInfo = &appInfo;
      if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
      } else {
        createInfo.enabledLayerCount = 0;
      }

      unsigned int count = 0;
      if(! SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
        std::cerr << "Could not retrieve extensions count" << std::endl;

      std::vector<const char*> extensions = {
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME
      };

      size_t additional_extension_count = extensions.size();
      extensions.resize(additional_extension_count + count);

      if (!SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data() + additional_extension_count))
        std::cerr << "Could not retrieve extended instance extensions" << std::endl;

#ifdef DEBUG
      //  populate supported extensions
      uint32_t extensionCount = 0;
      vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
      std::vector<VkExtensionProperties> supportedExtensions(extensionCount);
      vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, supportedExtensions.data());

      // Check for extension support
      std::cout << extensions.size() << " extensions needed :" <<std::endl;
      for(auto &extension : extensions){
        std::cout << "\t" << extension ;
        bool found = false;
        for(auto &supported : supportedExtensions) {
          if(strcmp(extension, supported.extensionName) == 0) {
            found = true;
            break;
          }
        }
        if(!found) {
          std::cout << " -> NOT SUPPORTED";
        }
        std::cout << std::endl;
      }
#endif


      createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
      createInfo.ppEnabledExtensionNames = extensions.data();

      if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        throw std::runtime_error("failed to create instance!");

    }

    bool checkValidationLayerSupport() {
      uint32_t layerCount;
      vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
      std::vector<VkLayerProperties> availableLayers(layerCount);
      vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

      for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
          if(strcmp(layerName, layerProperties.layerName) == 0) {
            layerFound = true;
            break;
          }
        }
        if (!layerFound) {
          return false;
        }
      }

      return true;
    }
};

int main() {
  HelloTriangleApplication app;

  try{
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

