FROM ubuntu:24.04 AS base
RUN apt-get update
RUN apt-get upgrade -y

FROM base AS frontend_build
RUN apt-get install -y g++ cmake git python3 xz-utils ninja-build
WORKDIR /builder
RUN git clone -b 4.0.15 https://github.com/emscripten-core/emsdk.git
RUN cd emsdk && ./emsdk install latest
RUN cd emsdk && ./emsdk activate latest
COPY frontend frontend
RUN cd emsdk && . ./emsdk_env.sh && cd .. && emcmake cmake -S frontend -B frontend-build -G Ninja
RUN cmake --build frontend-build

FROM base AS backend_build
RUN apt-get install -y gcc libzip-dev
WORKDIR /builder
RUN apt-get install -y dotnet-sdk-8.0
COPY backend backend
RUN cd backend && dotnet build && dotnet publish

FROM base AS deploy
RUN apt-get install -y libicu-dev
RUN useradd --create-home --shell /usr/bin/bash runner
USER runner
WORKDIR /home/runner
RUN mkdir wwwroot
COPY --from=frontend_build /builder/frontend-build/opendrill.js /home/runner/wwwroot
COPY --from=frontend_build /builder/frontend-build/opendrill.wasm /home/runner/wwwroot
COPY --from=frontend_build /builder/frontend-build/index.html /home/runner/wwwroot
COPY --from=backend_build /builder/backend/bin/Release/net8.0/linux-x64/publish/backend .
COPY --from=backend_build /builder/backend/bin/Release/net8.0/linux-x64/publish/appsettings.json .
ENV ASPNETCORE_URLS="http://0.0.0.0:5000"
CMD [ "./backend" ]
