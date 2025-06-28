if ! command -v picotool &>/dev/null; then
    pushd ~
    
    git clone https://github.com/raspberrypi/pico-sdk.git $HOME/pico/pico-sdk
    cd $HOME/pico/pico-sdk
    git submodule update --init

    echo "picotool not found – installing locally"
    git clone https://github.com/raspberrypi/picotool.git
    
    cd picotool
    mkdir build && cd build
    cmake -DPICO_SDK_PATH=$HOME/pico/pico-sdk \
          -DCMAKE_INSTALL_PREFIX=$HOME/.local ..
    make -j$(nproc)
    make install
    popd
else
    echo "picotool already installed at $(command -v picotool)"
fi

echo $PATH | grep -q "$HOME/.local/bin" || echo 'export PATH=$HOME/.local/bin:$PATH' >> ~/.bashrc
