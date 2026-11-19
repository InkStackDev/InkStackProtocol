/**
 * @brief 搜索服务RPC协议定义
 * @note 搜索服务RPC协议定义
 */
#ifndef __PROTOCOL_SS_SEARCH_H__
#define __PROTOCOL_SS_SEARCH_H__

#include <chen/rpc/serializer.h>
#include <cstdint>
#include <string>
#include <vector>

#define SS_SEARCH_INDEX_VERSION      3 /* 搜索索引文件格式版本 */

#define SS_CMD_SEARCH_ARTICLES       200 /* 搜索文章 */
#define SS_CMD_SEARCH_UPSERT_DOC     201 /* 新增或更新搜索文档 */
#define SS_CMD_SEARCH_REMOVE_ARTICLE 202 /* 从搜索索引移除文章 */
#define SS_CMD_SEARCH_REBUILD_BEGIN  203 /* 开始全量重建 */
#define SS_CMD_SEARCH_REBUILD_DOCS   204 /* 推送全量重建文档 */
#define SS_CMD_SEARCH_REBUILD_COMMIT 205 /* 提交全量重建 */
#define SS_CMD_SEARCH_GET_STATS      206 /* 获取搜索服务状态 */

/**
 * @brief 搜索查询条件
 */
struct tagSearchQuery {
    std::string Keyword;               /* 关键词 */
    std::vector<uint64_t> CategoryIds; /* 分类ID列表 */
    std::vector<uint64_t> LabelIds;    /* 标签ID列表 */
    int32_t State;                     /* 文章状态，0表示不过滤 */
    int64_t Channel;                   /* 频道ID，0表示不过滤 */
    int64_t UserId;                    /* 作者ID，0表示不过滤 */
    std::string YearMonth;             /* 年月，例如 2026年11月 */
    int32_t Page;                      /* 页码，从1开始 */
    int32_t PageSize;                  /* 每页数量 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagSearchQuery> {
    static void write(ByteArray::ptr ba, const tagSearchQuery& u)
    {
        ba->writeStringVint(u.Keyword);
        ba->writeUint32(static_cast<uint32_t>(u.CategoryIds.size()));
        for (const auto& item : u.CategoryIds) {
            ba->writeFuint64(item);
        }
        ba->writeUint32(static_cast<uint32_t>(u.LabelIds.size()));
        for (const auto& item : u.LabelIds) {
            ba->writeFuint64(item);
        }
        ba->writeFint32(u.State);
        ba->writeFint64(u.Channel);
        ba->writeFint64(u.UserId);
        ba->writeStringVint(u.YearMonth);
        ba->writeFint32(u.Page);
        ba->writeFint32(u.PageSize);
    }

    static void read(ByteArray::ptr ba, tagSearchQuery& u)
    {
        u.Keyword = ba->readStringVint();
        {
            uint32_t count = ba->readUint32();
            u.CategoryIds.clear();
            u.CategoryIds.reserve(count);
            for (uint32_t i = 0; i < count; ++i) {
                uint64_t item{};
                item = ba->readFuint64();
                u.CategoryIds.push_back(item);
            }
        }
        {
            uint32_t count = ba->readUint32();
            u.LabelIds.clear();
            u.LabelIds.reserve(count);
            for (uint32_t i = 0; i < count; ++i) {
                uint64_t item{};
                item = ba->readFuint64();
                u.LabelIds.push_back(item);
            }
        }
        u.State = ba->readFint32();
        u.Channel = ba->readFint64();
        u.UserId = ba->readFint64();
        u.YearMonth = ba->readStringVint();
        u.Page = ba->readFint32();
        u.PageSize = ba->readFint32();
    }
};

/**
 * @brief 搜索文档
 */
struct tagSearchDoc {
    uint64_t ArticleId;                /* 文章ID */
    int64_t UserId;                    /* 作者ID */
    int32_t State;                     /* 文章状态 */
    int64_t Channel;                   /* 频道ID */
    int64_t PublishTime;               /* 发布时间 */
    int64_t Weight;                    /* 权重 */
    int64_t SearchUpdateTime;          /* 搜索文档更新时间（毫秒） */
    std::string Title;                 /* 文章标题 */
    std::string Content;               /* 文章内容 */
    std::vector<uint64_t> CategoryIds; /* 分类ID列表 */
    std::vector<uint64_t> LabelIds;    /* 标签ID列表 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagSearchDoc> {
    static void write(ByteArray::ptr ba, const tagSearchDoc& u)
    {
        ba->writeFuint64(u.ArticleId);
        ba->writeFint64(u.UserId);
        ba->writeFint32(u.State);
        ba->writeFint64(u.Channel);
        ba->writeFint64(u.PublishTime);
        ba->writeFint64(u.Weight);
        ba->writeFint64(u.SearchUpdateTime);
        ba->writeStringVint(u.Title);
        ba->writeStringVint(u.Content);
        ba->writeUint32(static_cast<uint32_t>(u.CategoryIds.size()));
        for (const auto& item : u.CategoryIds) {
            ba->writeFuint64(item);
        }
        ba->writeUint32(static_cast<uint32_t>(u.LabelIds.size()));
        for (const auto& item : u.LabelIds) {
            ba->writeFuint64(item);
        }
    }

    static void read(ByteArray::ptr ba, tagSearchDoc& u)
    {
        u.ArticleId = ba->readFuint64();
        u.UserId = ba->readFint64();
        u.State = ba->readFint32();
        u.Channel = ba->readFint64();
        u.PublishTime = ba->readFint64();
        u.Weight = ba->readFint64();
        u.SearchUpdateTime = ba->readFint64();
        u.Title = ba->readStringVint();
        u.Content = ba->readStringVint();
        {
            uint32_t count = ba->readUint32();
            u.CategoryIds.clear();
            u.CategoryIds.reserve(count);
            for (uint32_t i = 0; i < count; ++i) {
                uint64_t item{};
                item = ba->readFuint64();
                u.CategoryIds.push_back(item);
            }
        }
        {
            uint32_t count = ba->readUint32();
            u.LabelIds.clear();
            u.LabelIds.reserve(count);
            for (uint32_t i = 0; i < count; ++i) {
                uint64_t item{};
                item = ba->readFuint64();
                u.LabelIds.push_back(item);
            }
        }
    }
};

/**
 * @brief 搜索结果
 */
struct tagSearchResult {
    int32_t Code;              /* 错误码，0表示成功 */
    int32_t Total;             /* 命中总数 */
    std::vector<uint64_t> Ids; /* 当前页文章ID列表 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagSearchResult> {
    static void write(ByteArray::ptr ba, const tagSearchResult& u)
    {
        ba->writeFint32(u.Code);
        ba->writeFint32(u.Total);
        ba->writeUint32(static_cast<uint32_t>(u.Ids.size()));
        for (const auto& item : u.Ids) {
            ba->writeFuint64(item);
        }
    }

    static void read(ByteArray::ptr ba, tagSearchResult& u)
    {
        u.Code = ba->readFint32();
        u.Total = ba->readFint32();
        {
            uint32_t count = ba->readUint32();
            u.Ids.clear();
            u.Ids.reserve(count);
            for (uint32_t i = 0; i < count; ++i) {
                uint64_t item{};
                item = ba->readFuint64();
                u.Ids.push_back(item);
            }
        }
    }
};

/**
 * @brief 搜索服务状态
 */
struct tagSearchStats {
    int32_t Code;         /* 错误码，0表示成功 */
    bool Ready;           /* 索引是否就绪 */
    bool Rebuilding;      /* 是否正在全量重建 */
    uint64_t DocCount;    /* 文档数量 */
    int64_t LastSyncTime; /* 最后同步时间（毫秒） */
    int32_t IndexVersion; /* 索引版本 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagSearchStats> {
    static void write(ByteArray::ptr ba, const tagSearchStats& u)
    {
        ba->writeFint32(u.Code);
        ba->writeFint8(u.Ready ? 1 : 0);
        ba->writeFint8(u.Rebuilding ? 1 : 0);
        ba->writeFuint64(u.DocCount);
        ba->writeFint64(u.LastSyncTime);
        ba->writeFint32(u.IndexVersion);
    }

    static void read(ByteArray::ptr ba, tagSearchStats& u)
    {
        u.Code = ba->readFint32();
        u.Ready = ba->readFint8() != 0;
        u.Rebuilding = ba->readFint8() != 0;
        u.DocCount = ba->readFuint64();
        u.LastSyncTime = ba->readFint64();
        u.IndexVersion = ba->readFint32();
    }
};

/**
 * @brief 搜索服务错误码
 */
enum tagSearchError {
    SEARCH_OK = 0,            /* 成功 */
    SEARCH_NOT_READY = 1,     /* 索引未就绪 */
    SEARCH_INVALID_QUERY = 2, /* 查询参数无效 */
    SEARCH_BUSY = 3,          /* 服务忙，请稍后重试 */
    SEARCH_BAD_SNAPSHOT = 4,  /* 快照ID无效或已过期 */
    SEARCH_INTERNAL = 5       /* 内部错误 */
};

#endif // __PROTOCOL_SS_SEARCH_H__
