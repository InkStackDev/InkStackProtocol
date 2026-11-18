/**
 * @brief 文章服务对外 RPC 协议定义
 * @note 文章服务对外 RPC 协议定义
 */
#ifndef __PROTOCOL_ARTICLE_H__
#define __PROTOCOL_ARTICLE_H__

#include <chen/rpc/serializer.h>
#include <cstdint>
#include <string>

#define ARTICLE_CMD_GET_BRIEF      3001 /* 按文章 id 获取文章简介 */
#define ARTICLE_CMD_GET_BRIEFS     3002 /* 按文章 id 列表批量获取文章简介 */
#define ARTICLE_CMD_GET_STATS      3003 /* 获取文章统计（支持分类/角色/时间/关键词过滤） */
#define ARTICLE_CMD_GET_VIEW_STATS 3004 /* 获取浏览量统计（今日/累计/访客） */
#define ARTICLE_CMD_LIST_RECENT    3005 /* 获取最近文章列表（仪表盘用） */
#define ARTICLE_CMD_COUNT_BY_USER  3006 /* 统计指定用户的文章数 */

/**
 * @brief 文章简介（跨服务只读视图）
 */
struct tagArticleBrief {
    int64_t Id;          /* 文章 id，0 表示不存在 */
    int64_t UserId;      /* 作者用户 id */
    std::string Title;   /* 标题 */
    int32_t State;       /* 状态：见 ArticleManager::State */
    bool IsDeleted;      /* 是否已删除 */
    int64_t Views;       /* 浏览量 */
    int64_t Praise;      /* 点赞数 */
    int64_t Favorites;   /* 收藏数 */
    int64_t PublishTime; /* 发布时间（秒） */
    int64_t CreateTime;  /* 创建时间（秒） */
    int64_t UpdateTime;  /* 更新时间（秒） */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagArticleBrief> {
    static void write(ByteArray::ptr ba, const tagArticleBrief& u)
    {
        ba->writeFint64(u.Id);
        ba->writeFint64(u.UserId);
        ba->writeStringVint(u.Title);
        ba->writeFint32(u.State);
        ba->writeFint8(u.IsDeleted ? 1 : 0);
        ba->writeFint64(u.Views);
        ba->writeFint64(u.Praise);
        ba->writeFint64(u.Favorites);
        ba->writeFint64(u.PublishTime);
        ba->writeFint64(u.CreateTime);
        ba->writeFint64(u.UpdateTime);
    }

    static void read(ByteArray::ptr ba, tagArticleBrief& u)
    {
        u.Id = ba->readFint64();
        u.UserId = ba->readFint64();
        u.Title = ba->readStringVint();
        u.State = ba->readFint32();
        u.IsDeleted = ba->readFint8() != 0;
        u.Views = ba->readFint64();
        u.Praise = ba->readFint64();
        u.Favorites = ba->readFint64();
        u.PublishTime = ba->readFint64();
        u.CreateTime = ba->readFint64();
        u.UpdateTime = ba->readFint64();
    }
};

/**
 * @brief 文章统计
 */
struct tagArticleStats {
    int64_t Total;     /* 总数 */
    int64_t Pending;   /* 待审核数 */
    int64_t Published; /* 已发布数 */
    int64_t Rejected;  /* 已驳回数 */
    int64_t Reported;  /* 被举报数 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagArticleStats> {
    static void write(ByteArray::ptr ba, const tagArticleStats& u)
    {
        ba->writeFint64(u.Total);
        ba->writeFint64(u.Pending);
        ba->writeFint64(u.Published);
        ba->writeFint64(u.Rejected);
        ba->writeFint64(u.Reported);
    }

    static void read(ByteArray::ptr ba, tagArticleStats& u)
    {
        u.Total = ba->readFint64();
        u.Pending = ba->readFint64();
        u.Published = ba->readFint64();
        u.Rejected = ba->readFint64();
        u.Reported = ba->readFint64();
    }
};

/**
 * @brief 文章浏览量统计
 */
struct tagArticleViewStats {
    int64_t TodayViews;    /* 今日浏览量 */
    int64_t TotalViews;    /* 累计浏览量 */
    int64_t TotalVisitors; /* 累计访客数 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagArticleViewStats> {
    static void write(ByteArray::ptr ba, const tagArticleViewStats& u)
    {
        ba->writeFint64(u.TodayViews);
        ba->writeFint64(u.TotalViews);
        ba->writeFint64(u.TotalVisitors);
    }

    static void read(ByteArray::ptr ba, tagArticleViewStats& u)
    {
        u.TodayViews = ba->readFint64();
        u.TotalViews = ba->readFint64();
        u.TotalVisitors = ba->readFint64();
    }
};

#endif // __PROTOCOL_ARTICLE_H__
