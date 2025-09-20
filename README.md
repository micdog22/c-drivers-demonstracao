
# C Drivers Pack (Windows KMDF, C)

Pacote com **3 drivers KMDF em C** prontos para estudo e extensão, com solução `.sln` do Visual Studio/WDK:

1. **EchoDrv** — IOCTL de eco (retorna o que recebeu).
2. **RandomDrv** — IOCTL para preencher o buffer de saída com bytes pseudoaleatórios.
3. **NullDrv** — IOCTL que apenas consome dados e retorna sucesso.

Projetos projetados para compilar com **Visual Studio 2022** + **Windows Driver Kit (WDK) 10**. Cada driver inclui `.inf` para dispositivo **Root\*** e código mínimo de filas/IOCTL.

> Observação importante: código de **kernel-mode** exige ambiente correto e assinatura de teste. Use em VM e ative o **Test Mode** se necessário.

## Pré-requisitos

- Windows 10/11 x64
- Visual Studio 2022 (Desktop development with C++)
- **Windows 10/11 WDK** correspondente ao SDK instalado
- Ferramentas opcionais: `devcon.exe` (vem no WDK) para instalar dispositivos Root.

## Como compilar

1. Abra `CDriversPack.sln` no Visual Studio (com WDK instalado).
2. Selecione `x64` e `Debug` (ou `Release`).
3. Build Solution (`Ctrl+Shift+B`).

Saída gerada em `x64\Debug\*.sys` (ou `x64\Release`).

## Como instalar (devcon, Root-enum)

Exemplo com **EchoDrv**:

```bat
# Prompt do Desenvolvedor x64 para VS/WDK, com admin
devcon install drivers\EchoDrv\EchoDrv.inf Root\EchoDrv
devcon status *EchoDrv*
# desinstalar:
devcon remove Root\EchoDrv
```

Repita para `RandomDrv` e `NullDrv` com seus respectivos `.inf` e IDs `Root\RandomDrv` e `Root\NullDrv`.

## Interface de dispositivo

Cada driver expõe um **Device Interface** (GUID) para que aplicações user-mode possam abrir com `SetupDi`/`CreateFile` e usar `DeviceIoControl`:

- EchoDrv: `GUID_DEVINTERFACE_ECHODRV`
- RandomDrv: `GUID_DEVINTERFACE_RANDOMDRV`
- NullDrv: `GUID_DEVINTERFACE_NULLDRV`

## IOCTLs

Os IOCTLs são `METHOD_BUFFERED` e `FILE_ANY_ACCESS`:

- EchoDrv: `IOCTL_ECHO` — ecoa o buffer de entrada para a saída.
- RandomDrv: `IOCTL_RANDOM_FILL` — preenche a saída com bytes pseudoaleatórios até o tamanho do buffer.
- NullDrv: `IOCTL_NULL_SINK` — descarta a entrada, retorna sucesso.

Veja `Public.h` em cada projeto para os códigos `CTL_CODE`.

## Licença

MIT (veja `LICENSE`).
