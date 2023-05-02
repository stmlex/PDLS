set(DESKTOP_TARGET                  ws407_desktop)

set(IO_MOCK_DIR     ${DESKTOP_TARGET_PATH}/io_mock)
set(MOCKS_DIR       ${DESKTOP_TARGET_PATH}/mocks)

set(DESKTOP_INCLUDE_DIR
    ${DESKTOP_DIR}
    ${IO_MOCK_DIR}
    ${MOCKS_DIR}
    ${APP_DIRS}
)