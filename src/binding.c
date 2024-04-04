#define NAPI_VERSION 6
#include <node_api.h>


#define NODE_API_CALL(env, call)                                  \
  do {                                                            \
    napi_status status = (call);                                  \
    if (status != napi_ok) {                                      \
      const napi_extended_error_info* error_info = NULL;          \
      napi_get_last_error_info((env), &error_info);               \
      const char* err_message = error_info->error_message;        \
      bool is_pending;                                            \
      napi_is_exception_pending((env), &is_pending);              \
      /* If an exception is already pending, don't rethrow it */  \
      if (!is_pending) {                                          \
        const char* message = (err_message == NULL)               \
            ? "empty error message"                               \
            : err_message;                                        \
        napi_throw_error((env), NULL, message);                   \
      }                                                           \
      return NULL;                                                \
    }                                                             \
  } while(0)

#define NODE_SET_FUNCTION(env, exports, key, fn) \
  do {                                           \
    napi_value n_fn;                             \
    NODE_API_CALL(                               \
      env,                                       \
      napi_create_function(                      \
        env,                                     \
        NULL,                                    \
        0,                                       \
        fn,                                      \
        NULL,                                    \
        &n_fn                                    \
      )                                          \
    );                                           \
    NODE_API_CALL(                               \
      env,                                       \
      napi_set_named_property(                   \
        env,                                     \
        exports,                                 \
        key,                                     \
        n_fn                                     \
      )                                          \
    );                                           \
  } while(0)

napi_value get_from_i64(napi_env env, napi_callback_info info) {
  napi_value result;
  NODE_API_CALL(env, napi_create_bigint_int64(env, 1234, &result));
  return result;
}

napi_value get_from_words_1(napi_env env, napi_callback_info info) {
  napi_value result;
  const uint64_t words[] = {1234};
  NODE_API_CALL(env, napi_create_bigint_words(env, 0, 1, &words[0], &result));
  return result;
}

napi_value get_from_words_2(napi_env env, napi_callback_info info) {
  napi_value result;
  uint64_t words[] = {1234, 5678};
  NODE_API_CALL(env, napi_create_bigint_words(env, 0, 2, &words[0], &result));
  return result;
}

NAPI_MODULE_INIT() {
  NODE_SET_FUNCTION(env, exports, "getFromI64", get_from_i64);
  NODE_SET_FUNCTION(env, exports, "getFromWords1", get_from_words_1);
  NODE_SET_FUNCTION(env, exports, "getFromWords2", get_from_words_2);
  return exports;
}
