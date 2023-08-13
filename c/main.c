#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SHA256_BLOCK_SIZE 64
#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

typedef struct {
    uint32_t total[2];
    uint32_t state[8];
    uint8_t buffer[SHA256_BLOCK_SIZE];
} sha256_ctx;

void sha256_init(sha256_ctx *ctx) {
    ctx->total[0] = 0;
    ctx->total[1] = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

void sha256_transform(sha256_ctx *ctx) {
    // Implementation of the SHA-256 transformation steps
    // ...

    // Example: A simple transformation loop (not the actual algorithm)
    for (int i = 0; i < 64; i++) {
        // Placeholder code for demonstration
        // Replace this with the actual transformation logic
        ctx->state[i % 8] += ctx->buffer[i % 64];
    }
}

void sha256_update(sha256_ctx *ctx, const uint8_t *data, uint32_t len) {
    // Implementation of the SHA-256 update logic
    // ...

    // Example: Copying data to buffer and calling transform
    for (uint32_t i = 0; i < len; i++) {
        ctx->buffer[ctx->total[0] % SHA256_BLOCK_SIZE] = data[i];
        ctx->total[0]++;
        if (ctx->total[0] % SHA256_BLOCK_SIZE == 0) {
            sha256_transform(ctx);
        }
    }
}

void sha256_final(sha256_ctx *ctx, uint8_t *digest) {
    // Implementation of the SHA-256 finalization logic
    // ...

    // Example: Padding and final transformation
    ctx->buffer[ctx->total[0] % SHA256_BLOCK_SIZE] = 0x80;
    if (ctx->total[0] % SHA256_BLOCK_SIZE >= 56) {
        sha256_transform(ctx);
    }
    ctx->total[0] += 64 - (ctx->total[0] % SHA256_BLOCK_SIZE);
    ctx->buffer[56] = ctx->total[1];
    ctx->buffer[57] = ctx->total[1] >> 8;
    ctx->buffer[58] = ctx->total[1] >> 16;
    ctx->buffer[59] = ctx->total[1] >> 24;
    ctx->buffer[60] = ctx->total[0];
    ctx->buffer[61] = ctx->total[0] >> 8;
    ctx->buffer[62] = ctx->total[0] >> 16;
    ctx->buffer[63] = ctx->total[0] >> 24;
    sha256_transform(ctx);

    // Copy the final hash to the digest
    for (int i = 0; i < 8; i++) {
        digest[i * 4 + 0] = ctx->state[i] >> 24;
        digest[i * 4 + 1] = ctx->state[i] >> 16;
        digest[i * 4 + 2] = ctx->state[i] >> 8;
        digest[i * 4 + 3] = ctx->state[i];
    }
}

void sha256(const uint8_t *data, uint32_t len, uint8_t *digest) {
    sha256_ctx ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, data, len);
    sha256_final(&ctx, digest);
}

int main() {
    char inputString[] = "Hello, world!";
    uint8_t outputBuffer[32]; // SHA-256 produces a 256-bit (32-byte) hash

    sha256((const uint8_t *)inputString, strlen(inputString), outputBuffer);

    printf("Original String: %s\n", inputString);
    printf("SHA-256 Hash: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", outputBuffer[i]);
    }
    printf("\n");
    getchar();

    return 0;
}
