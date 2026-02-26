#include <cstring>
#include <format>
#include <print>
#include <cmath>  // 需要包含cmath用于计算

#include "payload/PartitionInfo.h"
#include "payload/Utils.h"

namespace skkk {
	void FileOperation::initExcInfo(int errCode) const {
		excInfo = std::format("name: {:18s}, type: {}, code({}): {:s}",
		                      partName, errCode, type, strerror(abs(errCode)));
	}

	std::string formatSize(uint64_t size) {
		if (size >= 1073741824) {
			double sizeInGB = static_cast<double>(size) / 1073741824.0;
			return std::format("{:.1f}G", sizeInGB);
		} else if (size >= 1048576) {
			double sizeInMB = static_cast<double>(size) / 1048576.0;
			return std::format("{:.1f}MB", sizeInMB);
		} else if (size >= 1024) {
			double sizeInKB = static_cast<double>(size) / 1024.0;
			return std::format("{:.0f}kb", sizeInKB);
		} else {
			return std::format("{}b", size);
		}
	}

	PartitionInfo::PartitionInfo(const std::string &name, uint64_t size, const std::string &outFilePath,
	                             uint32_t blockSize, const std::string &oldHash, uint64_t oldHashSize,
	                             const std::string &newHash,
	                             uint64_t newHashSize)
		: name(name),
		  size(size),
		  outFilePath(outFilePath),
		  blockSize(blockSize),
		  oldHash(oldHash),
		  oldHashSize(oldHashSize),
		  newHash(newHash),
		  newHashSize(newHashSize) {
		oldHashHexStr = bytesToHexString(reinterpret_cast<const uint8_t *>(oldHash.data()),
		                                 oldHash.size());
		newHashHexStr = bytesToHexString(reinterpret_cast<const uint8_t *>(newHash.data()),
		                                 newHash.size());
	}

	void PartitionInfo::printInfo() const {
		std::string formattedSize = formatSize(size);
		std::println("{}|{} 「大小：{}」", name, name, formattedSize);
	}

	bool PartitionInfo::checkExtractionSuccessful() const {
		isExtractionSuccessful = excInfos.empty() &&
		                         *extractProgress == operations.size();
		return isExtractionSuccessful;
	}

	void PartitionInfo::initExcInfoByInitFd(const std::string &path, int errCode) const {
		std::unique_lock lock{*mutex_};
		std::string msg = std::format("Create/Open file err: '{}', code({}): {:s}",
		                              path, errCode, strerror(abs(errCode)));
		excInfos.emplace_back(msg);
	}

	void PartitionInfo::initExcInfos() const {
		for (const auto &operation: operations) {
			auto &info = operation.excInfo;
			if (!info.empty())
				excInfos.emplace_back(info);
		}
	}

	void PartitionInfo::ifExcExistsWrite2File() const {
		if (!isExtractionSuccessful) {
			if (auto *file = fopen(outErrorPath.c_str(), "wb")) {
				for (const auto &info: excInfos) {
					fprintf(file, "%s\n", info.c_str());
				}
				fclose(file);
			}
		}
	}

	void PartitionInfo::resetStatus() const {
		*extractProgress = 0;
		isExtractionSuccessful = false;
		excInfos.clear();
		for (const auto &operation: operations) {
			operation.excInfo.clear();
		}
	}
}
