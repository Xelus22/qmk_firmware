// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <board.h>

#define BOARD_OTG2_USES_ULPI

#define GPIOA_PIN0                  0U
#define GPIOA_PIN1                  1U
#define GPIOA_PIN2                  2U
#define GPIOA_USB_OTG_HS_D0         3U
#define GPIOA_PIN4                  4U
#define GPIOA_USB_OTG_HS_CK         5U
#define GPIOA_PIN6                  6U
#define GPIOA_PIN7                  7U
#define GPIOA_PIN8                  8U
#define GPIOA_PIN9                  9U
#define GPIOA_OTG_FS_ID             10U
#define GPIOA_OTG_FS_DM             11U
#define GPIOA_OTG_FS_DP             12U
#define GPIOA_PIN13                 13U
#define GPIOA_PIN14                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_USB_OTG_HS_D1         0U
#define GPIOB_USB_OTG_HS_D2         1U
#define GPIOB_PIN2                  2U
#define GPIOB_PIN3                  3U
#define GPIOB_PIN4                  4U
#define GPIOB_USB_OTG_HS_D7         5U
#define GPIOB_PIN6                  6U
#define GPIOB_PIN7                  7U
#define GPIOB_PIN8                  8U
#define GPIOB_PIN9                  9U
#define GPIOB_USB_OTG_HS_D3         10U
#define GPIOB_USB_OTG_HS_D4         11U
#define GPIOB_USB_OTG_HS_D5         12U
#define GPIOB_USB_OTG_HS_D6         13U
#define GPIOB_PIN14                 14U
#define GPIOB_PIN15                 15U

#define GPIOC_USB_OTG_HS_STP        0U
#define GPIOC_PIN1                  1U
#define GPIOC_USB_OTG_HS_DIR        2U
#define GPIOC_USB_OTG_HS_NXT        3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#undef  VAL_GPIOA_MODER
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_PIN0) |              \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |              \
                                     PIN_MODE_INPUT(GPIOA_PIN2) |              \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_OTG_HS_D0) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN4) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_OTG_HS_CK) | \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN6) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN7) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |              \
                                     PIN_MODE_INPUT(GPIOA_PIN9) |              \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_ID) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DM) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DP) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN13) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_PIN14) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN15))
#undef  VAL_GPIOA_OTYPER
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PIN0) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN1) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN2) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_OTG_HS_D0) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN4) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_OTG_HS_CK) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN6) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN7) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN9) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_ID) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DM) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DP) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN13) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN14) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#undef  VAL_GPIOA_OSPEEDR
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_PIN0) |             \
                                     PIN_OSPEED_HIGH(GPIOA_PIN1) |             \
                                     PIN_OSPEED_HIGH(GPIOA_PIN2) |             \
                                     PIN_OSPEED_HIGH(GPIOA_USB_OTG_HS_D0) |    \
                                     PIN_OSPEED_HIGH(GPIOA_PIN4) |             \
                                     PIN_OSPEED_HIGH(GPIOA_USB_OTG_HS_CK) |    \
                                     PIN_OSPEED_MEDIUM(GPIOA_PIN6) |           \
                                     PIN_OSPEED_MEDIUM(GPIOA_PIN7) |           \
                                     PIN_OSPEED_HIGH(GPIOA_PIN8) |             \
                                     PIN_OSPEED_HIGH(GPIOA_PIN9) |             \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_ID) |        \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_DM) |        \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_DP) |        \
                                     PIN_OSPEED_HIGH(GPIOA_PIN13) |            \
                                     PIN_OSPEED_HIGH(GPIOA_PIN14) |            \
                                     PIN_OSPEED_HIGH(GPIOA_PIN15))
#undef  VAL_GPIOA_PUPDR
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_PIN0) |          \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN1) |            \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN2) |            \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_OTG_HS_D0) | \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN4) |          \
                                     PIN_PUPDR_PULLUP(GPIOA_USB_OTG_HS_CK) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN6) |          \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN7) |          \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN8) |            \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN9) |          \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_ID) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DM) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DP) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN13) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN14) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN15))
#undef  VAL_GPIOA_ODR
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_PIN0) |                \
                                     PIN_ODR_HIGH(GPIOA_PIN1) |                \
                                     PIN_ODR_HIGH(GPIOA_PIN2) |                \
                                     PIN_ODR_HIGH(GPIOA_USB_OTG_HS_D0) |       \
                                     PIN_ODR_HIGH(GPIOA_PIN4) |                \
                                     PIN_ODR_HIGH(GPIOA_USB_OTG_HS_CK) |       \
                                     PIN_ODR_HIGH(GPIOA_PIN6) |                \
                                     PIN_ODR_HIGH(GPIOA_PIN7) |                \
                                     PIN_ODR_HIGH(GPIOA_PIN8) |                \
                                     PIN_ODR_HIGH(GPIOA_PIN9) |                \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_ID) |           \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DM) |           \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DP) |           \
                                     PIN_ODR_HIGH(GPIOA_PIN13) |               \
                                     PIN_ODR_HIGH(GPIOA_PIN14) |               \
                                     PIN_ODR_HIGH(GPIOA_PIN15))
#undef  VAL_GPIOA_AFRL
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PIN0, 0U) |             \
                                     PIN_AFIO_AF(GPIOA_PIN1, 0U) |             \
                                     PIN_AFIO_AF(GPIOA_PIN2, 0U) |             \
                                     PIN_AFIO_AF(GPIOA_USB_OTG_HS_D0, 10U) |   \
                                     PIN_AFIO_AF(GPIOA_PIN4, 6U) |             \
                                     PIN_AFIO_AF(GPIOA_USB_OTG_HS_CK, 10U) |   \
                                     PIN_AFIO_AF(GPIOA_PIN6, 5U) |             \
                                     PIN_AFIO_AF(GPIOA_PIN7, 5U))
#undef  VAL_GPIOA_AFRH
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0U) |             \
                                     PIN_AFIO_AF(GPIOA_PIN9, 0U) |             \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_ID, 10U) |       \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DM, 10U) |       \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DP, 10U) |       \
                                     PIN_AFIO_AF(GPIOA_PIN13, 0U) |            \
                                     PIN_AFIO_AF(GPIOA_PIN14, 0U) |            \
                                     PIN_AFIO_AF(GPIOA_PIN15, 0U))
#undef  VAL_GPIOB_MODER
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D1) | \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D2) | \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |              \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN3) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |              \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D7) | \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN6) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |              \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |              \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN9) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D3) | \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D4) | \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D5) | \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_OTG_HS_D6) | \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |             \
                                     PIN_MODE_INPUT(GPIOB_PIN15))
#undef  VAL_GPIOB_OTYPER
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D2) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN2) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN3) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D7) | \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_PIN6) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN7) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |          \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_PIN9) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D3) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D4) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D5) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_OTG_HS_D6) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN15))
#undef  VAL_GPIOB_OSPEEDR
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D1) |    \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D2) |    \
                                     PIN_OSPEED_HIGH(GPIOB_PIN2) |             \
                                     PIN_OSPEED_HIGH(GPIOB_PIN3) |             \
                                     PIN_OSPEED_HIGH(GPIOB_PIN4) |             \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D7) |    \
                                     PIN_OSPEED_HIGH(GPIOB_PIN6) |             \
                                     PIN_OSPEED_HIGH(GPIOB_PIN7) |             \
                                     PIN_OSPEED_HIGH(GPIOB_PIN8) |             \
                                     PIN_OSPEED_HIGH(GPIOB_PIN9) |             \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D3) |    \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D4) |    \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D5) |    \
                                     PIN_OSPEED_HIGH(GPIOB_USB_OTG_HS_D6) |    \
                                     PIN_OSPEED_HIGH(GPIOB_PIN14) |            \
                                     PIN_OSPEED_HIGH(GPIOB_PIN15))
#undef  VAL_GPIOB_PUPDR
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D1) | \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D2) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN2) |            \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN3) |          \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN4) |            \
                                     PIN_PUPDR_PULLUP(GPIOB_USB_OTG_HS_D7) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN6) |          \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN7) |            \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN8) |            \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN9) |          \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D3) | \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D4) | \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D5) | \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_OTG_HS_D6) | \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN14) |           \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN15))
#undef  VAL_GPIOB_ODR
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D1) |       \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D2) |       \
                                     PIN_ODR_HIGH(GPIOB_PIN2) |                \
                                     PIN_ODR_HIGH(GPIOB_PIN3) |                \
                                     PIN_ODR_HIGH(GPIOB_PIN4) |                \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D7) |       \
                                     PIN_ODR_HIGH(GPIOB_PIN6) |                \
                                     PIN_ODR_HIGH(GPIOB_PIN7) |                \
                                     PIN_ODR_HIGH(GPIOB_PIN8) |                \
                                     PIN_ODR_HIGH(GPIOB_PIN9) |                \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D3) |       \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D4) |       \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D5) |       \
                                     PIN_ODR_HIGH(GPIOB_USB_OTG_HS_D6) |       \
                                     PIN_ODR_HIGH(GPIOB_PIN14) |               \
                                     PIN_ODR_HIGH(GPIOB_PIN15))
#undef  VAL_GPIOB_AFRL
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_USB_OTG_HS_D1, 10U) |   \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D2, 10U) |   \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0U) |             \
                                     PIN_AFIO_AF(GPIOB_PIN3, 0U) |             \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0U) |             \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D7, 10U) |   \
                                     PIN_AFIO_AF(GPIOB_PIN6, 4U) |             \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0U))
#undef  VAL_GPIOB_AFRH
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0U) |             \
                                     PIN_AFIO_AF(GPIOB_PIN9, 4U) |             \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D3, 10U) |   \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D4, 10U) |   \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D5, 10U) |   \
                                     PIN_AFIO_AF(GPIOB_USB_OTG_HS_D6, 10U) |   \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0U) |            \
                                     PIN_AFIO_AF(GPIOB_PIN15, 0U))
#undef  VAL_GPIOC_MODER
#define VAL_GPIOC_MODER             (PIN_MODE_ALTERNATE(GPIOC_USB_OTG_HS_STP) |\
                                     PIN_MODE_INPUT(GPIOC_PIN1) |              \
                                     PIN_MODE_ALTERNATE(GPIOC_USB_OTG_HS_DIR) |\
                                     PIN_MODE_ALTERNATE(GPIOC_USB_OTG_HS_NXT) |\
                                     PIN_MODE_INPUT(GPIOC_PIN4) |              \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |              \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |              \
                                     PIN_MODE_ALTERNATE(GPIOC_PIN7) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |              \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |              \
                                     PIN_MODE_ALTERNATE(GPIOC_PIN10) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |             \
                                     PIN_MODE_ALTERNATE(GPIOC_PIN12) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |             \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |             \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#undef  VAL_GPIOC_OTYPER
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_USB_OTG_HS_STP) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOC_USB_OTG_HS_DIR) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_USB_OTG_HS_NXT) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |          \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN14) |         \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#undef  VAL_GPIOC_OSPEEDR
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_USB_OTG_HS_STP) |   \
                                     PIN_OSPEED_HIGH(GPIOC_PIN1) |             \
                                     PIN_OSPEED_HIGH(GPIOC_USB_OTG_HS_DIR) |   \
                                     PIN_OSPEED_HIGH(GPIOC_USB_OTG_HS_NXT) |   \
                                     PIN_OSPEED_HIGH(GPIOC_PIN4) |             \
                                     PIN_OSPEED_HIGH(GPIOC_PIN5) |             \
                                     PIN_OSPEED_HIGH(GPIOC_PIN6) |             \
                                     PIN_OSPEED_HIGH(GPIOC_PIN7) |             \
                                     PIN_OSPEED_HIGH(GPIOC_PIN8) |             \
                                     PIN_OSPEED_HIGH(GPIOC_PIN9) |             \
                                     PIN_OSPEED_HIGH(GPIOC_PIN10) |            \
                                     PIN_OSPEED_HIGH(GPIOC_PIN11) |            \
                                     PIN_OSPEED_HIGH(GPIOC_PIN12) |            \
                                     PIN_OSPEED_HIGH(GPIOC_PIN13) |            \
                                     PIN_OSPEED_HIGH(GPIOC_PIN14) |            \
                                     PIN_OSPEED_HIGH(GPIOC_PIN15))
#undef  VAL_GPIOC_PUPDR
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_USB_OTG_HS_STP) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |            \
                                     PIN_PUPDR_FLOATING(GPIOC_USB_OTG_HS_DIR) |\
                                     PIN_PUPDR_FLOATING(GPIOC_USB_OTG_HS_NXT) |\
                                     PIN_PUPDR_PULLUP(GPIOC_PIN4) |            \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN5) |            \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN6) |            \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN7) |          \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN8) |            \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN9) |            \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN10) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN11) |           \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN12) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN13) |           \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN14) |           \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN15))
#undef  VAL_GPIOC_ODR
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_USB_OTG_HS_STP) |      \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |                \
                                     PIN_ODR_HIGH(GPIOC_USB_OTG_HS_DIR) |      \
                                     PIN_ODR_HIGH(GPIOC_USB_OTG_HS_NXT) |      \
                                     PIN_ODR_HIGH(GPIOC_PIN4) |                \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |                \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |                \
                                     PIN_ODR_HIGH(GPIOC_PIN7) |                \
                                     PIN_ODR_HIGH(GPIOC_PIN8) |                \
                                     PIN_ODR_HIGH(GPIOC_PIN9) |                \
                                     PIN_ODR_HIGH(GPIOC_PIN10) |               \
                                     PIN_ODR_HIGH(GPIOC_PIN11) |               \
                                     PIN_ODR_HIGH(GPIOC_PIN12) |               \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |               \
                                     PIN_ODR_HIGH(GPIOC_PIN14) |               \
                                     PIN_ODR_HIGH(GPIOC_PIN15))
#undef  VAL_GPIOC_AFRL
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_USB_OTG_HS_STP, 10U) |  \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0U) |             \
                                     PIN_AFIO_AF(GPIOC_USB_OTG_HS_DIR, 10U) |  \
                                     PIN_AFIO_AF(GPIOC_USB_OTG_HS_NXT, 10U) |  \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0U) |             \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0U) |             \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |             \
                                     PIN_AFIO_AF(GPIOC_PIN7, 6U))
#undef  VAL_GPIOC_AFRH
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0U) |             \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0U) |             \
                                     PIN_AFIO_AF(GPIOC_PIN10, 6U) |            \
                                     PIN_AFIO_AF(GPIOC_PIN11, 0U) |            \
                                     PIN_AFIO_AF(GPIOC_PIN12, 6U) |            \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |            \
                                     PIN_AFIO_AF(GPIOC_PIN14, 0U) |            \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0U))
