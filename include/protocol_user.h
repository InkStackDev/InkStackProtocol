/**
 * @brief 用户服务对外 RPC 协议定义
 * @note 用户服务对外 RPC 协议定义
 */
#ifndef __PROTOCOL_USER_H__
#define __PROTOCOL_USER_H__

#include <chen/rpc/serializer.h>
#include <cstdint>
#include <string>

#define USER_CMD_GET_BRIEF         1001 /* 按用户 id 获取用户简介 */
#define USER_CMD_GET_BRIEFS        1002 /* 按用户 id 列表批量获取用户简介 */
#define USER_CMD_GET_ALL_IDS       1003 /* 获取全部用户 id（仅未删除） */
#define USER_CMD_GET_FOLLOW_COUNTS 1004 /* 获取用户关注数/粉丝数 */
#define USER_CMD_IS_FOLLOWING      1005 /* 判断 uid 是否关注了 target */
#define USER_CMD_GET_AI_CONFIG     1006 /* 获取用户的 AI 配置 */

/**
 * @brief 用户简介（跨服务只读视图）
 */
struct tagUserBrief {
    int64_t Id;         /* 用户 id，0 表示不存在 */
    std::string Name;   /* 用户名 */
    std::string Avatar; /* 头像地址 */
    std::string Email;  /* 邮箱 */
    int32_t Role;       /* 角色：见 UserManager::Role */
    int32_t State;      /* 状态：见 UserManager::Status */
    bool IsDeleted;     /* 是否已删除 */
    int64_t UpdateTime; /* 更新时间（秒），用于缓存失效判断 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagUserBrief> {
    static void write(ByteArray::ptr ba, const tagUserBrief& u)
    {
        ba->writeFint64(u.Id);
        ba->writeStringVint(u.Name);
        ba->writeStringVint(u.Avatar);
        ba->writeStringVint(u.Email);
        ba->writeFint32(u.Role);
        ba->writeFint32(u.State);
        ba->writeFint8(u.IsDeleted ? 1 : 0);
        ba->writeFint64(u.UpdateTime);
    }

    static void read(ByteArray::ptr ba, tagUserBrief& u)
    {
        u.Id = ba->readFint64();
        u.Name = ba->readStringVint();
        u.Avatar = ba->readStringVint();
        u.Email = ba->readStringVint();
        u.Role = ba->readFint32();
        u.State = ba->readFint32();
        u.IsDeleted = ba->readFint8() != 0;
        u.UpdateTime = ba->readFint64();
    }
};

/**
 * @brief 用户关注统计
 */
struct tagUserFollowCounts {
    int64_t Followers; /* 粉丝数 */
    int64_t Following; /* 关注数 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagUserFollowCounts> {
    static void write(ByteArray::ptr ba, const tagUserFollowCounts& u)
    {
        ba->writeFint64(u.Followers);
        ba->writeFint64(u.Following);
    }

    static void read(ByteArray::ptr ba, tagUserFollowCounts& u)
    {
        u.Followers = ba->readFint64();
        u.Following = ba->readFint64();
    }
};

/**
 * @brief 用户 AI 配置（跨服务只读视图）
 */
struct tagUserAiConfig {
    std::string Type;   /* 服务商类型：glm/openai/deepseek/claude，空表示未配置 */
    std::string Model;  /* 模型名称 */
    std::string Url;    /* 自定义接口地址 */
    std::string ApiKey; /* 加密后的 API Key */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagUserAiConfig> {
    static void write(ByteArray::ptr ba, const tagUserAiConfig& u)
    {
        ba->writeStringVint(u.Type);
        ba->writeStringVint(u.Model);
        ba->writeStringVint(u.Url);
        ba->writeStringVint(u.ApiKey);
    }

    static void read(ByteArray::ptr ba, tagUserAiConfig& u)
    {
        u.Type = ba->readStringVint();
        u.Model = ba->readStringVint();
        u.Url = ba->readStringVint();
        u.ApiKey = ba->readStringVint();
    }
};

#endif // __PROTOCOL_USER_H__
