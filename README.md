# Backbone - A Custom DNS Server with Extended Capabilities

## 👋 Introduction

Backbone is a next-generation DNS server that transcends traditional domain name resolution. Designed for developers and system architects who require more than standard RFC 1035 implementations, Backbone offers a flexible, high-performance solution for custom domain ecosystems.

Unlike conventional DNS servers, Backbone provides:
- Granular control over domain resolution
- Support for specialized application environments
- Efficient resource management for diverse computing platforms

## ✨ Features

- **Custom TLD Support**: Resolve and manage custom top-level domains to create self-contained web ecosystems.
- **Flexible DNS Records**: Add and manage custom DNS record types tailored for specific application needs.
- **Efficient Caching**: Advanced LRU and LFU caching mechanisms ensure optimal performance, even on embedded systems.
- **RFC 1035 Compliance**: Full compatibility with standard DNS requests and responses while offering extended functionality.
- **Interoperability**: Smoothly integrates with traditional DNS servers while maintaining autonomy over custom configurations.

## 🚀 Use Cases

Backbone is not just a DNS server; it's a versatile platform for innovative networking solutions:

1. **Custom Web Ecosystems**
   - Create isolated, self-contained network environments
   - Develop internal testing and staging domains
   - Prototype complex networking architectures without external dependencies

2. **Enhanced Browser and Application Integration**
   - Power custom browsers like Steve Browser with advanced domain handling
   - Implement application-specific domain resolution strategies
   - Enable seamless cross-application domain management

3. **Embedded and Resource-Constrained Systems**
   - Deploy a lightweight, efficient DNS resolver on IoT devices
   - Implement custom domain logic in edge computing scenarios
   - Optimize network performance in bandwidth-limited environments

## 🛠️ Technical Architecture

### Design Philosophy
Backbone is engineered with a focus on:
- **Performance**: Minimal overhead and high-throughput domain resolution
- **Flexibility**: Modular design supporting extensive customization
- **Standards Compliance**: Robust implementation of core DNS protocols

### Key Technical Components

- **Modern C++ Implementation**
  - Leverages C++23 features for memory efficiency
  - Zero-cost abstractions for high-performance networking
  - Smart pointer and RAII principles for robust memory management

- **Advanced Caching Mechanisms**
  - Hybrid Least Recently Used (LRU) and Least Frequently Used (LFU) caching
  - Configurable cache eviction policies
  - Intelligent cache warmup and preemptive resolution strategies

- **Dynamic Configuration**
  - Runtime configuration updates without server restart
  - JSON-based configuration for easy integration
  - Support for hot-reloading domain and record configurations

## 📦 Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yogesh-aggarwal/backbone.git
   cd backbone
   ```
2. (Optional) Configure custom TLDs and DNS records in `config.json`. Example:
   ```json
   {
      "tlds": ["example", "custom"],
      "records": {
         "example.custom": "192.168.1.1",
         "api.custom": "10.0.0.1"
      }
   }
   ```
3. Build and run the project using CMake:
   ```bash
   make run
   ```

## 🛠️ Building with CMake

### Build Targets

- `make all` (equivalent to `make clean build`)
- `make clean` - Removes the build directory
- `make generate` - Initializes the CMake build system
- `make build` - Compiles the project with CMake

## 🌱 Local Development Guide

### For Running

Build the project using the provided Makefile or CMake.

### For Hacking Around

1. Create a folder named `test` inside the `cmd` directory:
   ```bash
   mkdir cmd/test
   ```

2. Inside `cmd/test`, create a `CMakeLists.txt` file with the following content:
   ```cmake
   # Add executable for `test`
   add_executable(test main.cpp)

   # Link the backbone library (from the `source` folder)
   target_link_libraries(test PRIVATE backbone)
   ```

3. In `cmd/test`, create a C++ file (e.g., `main.cpp`) and begin using headers from the Backbone project:
   ```cpp
   #include <backbone/your_desired_header_file.hpp>
   ```

**Note**: This test directory and its contents will not be committed to Git.

#### Contribution Workflow
1. Fork the repository
2. Create a feature branch
3. Implement your changes
4. Write comprehensive tests
5. Submit a pull request with a detailed description

### Code Quality Standards
- Adhere to modern C++ best practices
- Maintain high test coverage
- Document new features and architectural decisions

## 📊 Performance Metrics

### Benchmarking Results
- Low-latency domain resolution
- Minimal memory footprint
- Horizontal scalability

### Resource Efficiency
- Configurable for various system constraints
- Optimized for embedded to enterprise-scale deployments

## 🏗️ Architecture Overview

- **Resolver**: Handles DNS queries, supports recursive and iterative lookups
- **Cache Manager**: Implements hybrid LRU/LFU caching for improved efficiency
- **Record Manager**: Manages dynamic DNS record entries and updates
- **Configuration Loader**: Reads and applies custom configurations from `config.json`
- **Server**: Main entry point for the DNS server, initializes and manages components

## 🔮 Future Roadmap

Backbone is more than a DNS server—it's a platform for network innovation. Upcoming features include:
- Enhanced security protocols
- More sophisticated caching algorithms
- Expanded custom record type support

Join us in reshaping domain resolution technology!

## 🤝 Contributing

Contributions are welcome! Please read the [CONTRIBUTING.md](./CONTRIBUTING.md) file for guidelines.

## 🛡️ License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.

## 👨‍💻 Author

**Yogesh Aggarwal**  
- [Portfolio](https://yogeshaggarwal.in)
- [LinkedIn](https://linkedin.com/in/yogeshdev215)

## 📞 Contact

For queries or support, please contact the author at [contact@yogeshaggarwal.in](mailto:contact@yogeshaggarwal.in).
