/**
 * @brief 评论服务对外 RPC 协议定义
 * @note 评论服务对外 RPC 协议定义
 */
#ifndef __PROTOCOL_COMMENT_H__
#define __PROTOCOL_COMMENT_H__

#include <chen/rpc/serializer.h>
#include <cstdint>
#include <string>

#define COMMENT_CMD_COUNT_BY_ARTICLE 4001 /* 统计指定文章的评论数 */
#define COMMENT_CMD_GET_STATS        4002 /* 获取评论统计 */
#define COMMENT_CMD_LIST_RECENT      4003 /* 获取最近评论列表（仪表盘/动态用） */
#define COMMENT_CMD_GET_BRIEFS       4004 /* 按评论 id 列表批量获取评论简介 */

/**
 * @brief 评论简介（跨服务只读视图）
 */
struct tagCommentBrief {
    int64_t Id;          /* 评论 id，0 表示不存在 */
    int64_t ArticleId;   /* 所属文章 id */
    int64_t UserId;      /* 评论者用户 id */
    std::string Content; /* 评论内容 */
    int32_t Status;      /* 审核状态：见 CommentManager::Status */
    bool IsDeleted;      /* 是否已删除 */
    int64_t CreateTime;  /* 创建时间（秒） */
    int64_t UpdateTime;  /* 更新时间（秒） */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagCommentBrief> {
    static void write(ByteArray::ptr ba, const tagCommentBrief& u)
    {
        ba->writeFint64(u.Id);
        ba->writeFint64(u.ArticleId);
        ba->writeFint64(u.UserId);
        ba->writeStringVint(u.Content);
        ba->writeFint32(u.Status);
        ba->writeFint8(u.IsDeleted ? 1 : 0);
        ba->writeFint64(u.CreateTime);
        ba->writeFint64(u.UpdateTime);
    }

    static void read(ByteArray::ptr ba, tagCommentBrief& u)
    {
        u.Id = ba->readFint64();
        u.ArticleId = ba->readFint64();
        u.UserId = ba->readFint64();
        u.Content = ba->readStringVint();
        u.Status = ba->readFint32();
        u.IsDeleted = ba->readFint8() != 0;
        u.CreateTime = ba->readFint64();
        u.UpdateTime = ba->readFint64();
    }
};

/**
 * @brief 评论统计
 */
struct tagCommentStats {
    int64_t Total;    /* 总数 */
    int64_t Pending;  /* 待审核数 */
    int64_t Approved; /* 已通过数 */
    int64_t Spam;     /* 垃圾评论数 */
    int64_t Reported; /* 被举报数 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagCommentStats> {
    static void write(ByteArray::ptr ba, const tagCommentStats& u)
    {
        ba->writeFint64(u.Total);
        ba->writeFint64(u.Pending);
        ba->writeFint64(u.Approved);
        ba->writeFint64(u.Spam);
        ba->writeFint64(u.Reported);
    }

    static void read(ByteArray::ptr ba, tagCommentStats& u)
    {
        u.Total = ba->readFint64();
        u.Pending = ba->readFint64();
        u.Approved = ba->readFint64();
        u.Spam = ba->readFint64();
        u.Reported = ba->readFint64();
    }
};

#endif // __PROTOCOL_COMMENT_H__
