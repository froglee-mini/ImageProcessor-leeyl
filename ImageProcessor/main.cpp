/**
 * @file main.cpp
 * @brief ImageProcessor 진입점 — 지원자가 작성해야 할 파일입니다.
 *
 * BMP 입출력과 커맨드라인 파싱은 제공된 코드가 처리합니다.
 * 본 과제에서 작성해야 할 것은 단 하나입니다:
 *
 *     ▶ 이미지 처리 필터 2개 이상 구현 + main 의 TODO 위치에 연결
 *
 * 또한 일관된 컨벤션과 예외 처리, 메모리 안정성도 함께 평가됩니다.
 */

#include "BmpParser.h"
#include "CommandLineParser.h"
#include "ImageBuffer.h"
#include "Exceptions.h"


#include <iostream>

 // TODO: 본인이 구현한 필터 헤더를 include 하세요.
#include "FilterFactory.h"
#include "Logger.h"

 // ...

#include <memory>
#include <vector>
#include <string>
#include <chrono>


int main(int argc, char* argv[]) {
    const auto startTime = std::chrono::steady_clock::now();
    std::string filterInfo = "(not parsed)";

    auto writeLog = [&](bool success, const std::string& error = "") {
        const auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - startTime
            ).count();

        try {
            ip::Logger::write(
                success, elapsed, filterInfo, error);
        }
        catch (const std::exception& e) {
            std::cerr << "Logging warning: "
                << e.what() << '\n';
        }
    };

    try {
        // ── CLI 인자 파싱 (제공된 코드) ─────────────────────────
        const ip::ProgramOptions options = ip::CommandLineParser::parse(argc, argv);

        filterInfo = options.pipeline.empty()
            ? options.filterName
            : options.pipeline;

        // ── BMP 로드 (제공된 코드) ──────────────────────────────
        ip::ImageBuffer image = ip::BmpParser::loadFromFile(options.inputPath);
        std::cout << "Loaded: " << image.width() << " x " << image.height() << "\n";

        // ───────────────────────────────────────────────────────
        // TODO: options.filterName 에 따라 적절한 필터를 생성하고
        //       image 에 적용하세요.
        //
        //   예시 코드 (참고용):
        //
        //     if (options.filterName == "grayscale") {
        //         GrayscaleFilter filter;
        //         filter.apply(image);
        //     }
        //     else if (options.filterName == "threshold:128") {
        //         ThresholdFilter filter(128);
        //         filter.apply(image);
        //     }
        //     else {
        //         throw ip::FilterError("Unknown filter: " + options.filterName);
        //     }
        //
        //   ※ 가산점 항목:
        //     - 추상 클래스(FilterBase) 기반 다형성 설계
        //     - 필터 파이프라인 체인 (CLI 옵션 확장 필요)
        //     - 멀티쓰레드 처리
        //     - 로그 파일 출력 (CLI 옵션 확장 필요)
        // ───────────────────────────────────────────────────────

        // ↓ 여기에 필터 적용 코드를 작성하세요.

        std::vector<std::unique_ptr<ip::FilterBase>> filters;

        if (options.pipeline.empty()) {
            // 기존 --filter 명령어는 그대로 처리
            filters.push_back(
                ip::FilterFactory::create(options.filterName));
        }
        else {
            const std::string& pipeline = options.pipeline;

            // | 가 있으면 |로 분리, 없으면 쉼표로 분리
            const char separator =
                pipeline.find('|') != std::string::npos ? '|' : ',';

            std::size_t start = 0;

            while (start < pipeline.size()) {
                const std::size_t end = pipeline.find(separator, start);

                const std::string name = pipeline.substr(
                    start,
                    end == std::string::npos ? end : end - start);

                if (name.empty()) {
                    throw ip::FilterError("Empty pipeline filter");
                }

                filters.push_back(ip::FilterFactory::create(name));

                if (end == std::string::npos) {
                    break;
                }

                start = end + 1;
            }

            if (pipeline.back() == separator) {
                throw ip::FilterError("Empty pipeline filter");
            }
        }

        // 모든 필터를 순서대로 적용
        for (const auto& filter : filters) {
            filter->apply(image);
        }

        // ── BMP 저장 (제공된 코드) ──────────────────────────────
        ip::BmpParser::saveToFile(options.outputPath, image);
        std::cout << "Saved:  " << options.outputPath << "\n";
        writeLog(true);
        return 0;
    }
    catch (const ip::ArgumentError& e) {
        std::cerr << e.what() << "\n\n";
        ip::CommandLineParser::printUsage(argc > 0 ? argv[0] : "ImageProcessor");
        writeLog(false, e.what());
        return 4;
    }
    catch (const ip::BmpParseError& e) {
        std::cerr << e.what() << std::endl;
        writeLog(false, e.what());
        return 2;
    }
    catch (const ip::FilterError& e) {
        std::cerr << e.what() << std::endl;
        writeLog(false, e.what());
        return 3;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        writeLog(false, e.what());
        return 1;
    }
}
