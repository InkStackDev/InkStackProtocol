/**
 * @brief 搜索服务RPC协议定义
 * @note 搜索服务RPC协议定义
 */
#ifndef __PROTOCOL_SEARCH_H__
#define __PROTOCOL_SEARCH_H__

#include <chen/rpc/serializer.h>
#include <cstdint>
#include <string>
#include <vector>

#define SS_CMD_SEARCH_QUERY   200 /* 搜索文章 */
#define SS_CMD_SEARCH_REINDEX 201 /* 重新索引单篇文章 */
#define SS_CMD_SEARCH_REBUILD 202 /* 全量重建索引 */
#define SS_CMD_SEARCH_HEALTH  203 /* 搜索服务健康状态 */

/**
 * @brief 服务注册功能类型
 */
enum tagSearchFunc {
    SS_FUNC_ID_SEARCH = 1, /* 搜索服务 */
    SS_FUNC_ID_API = 2,    /* API 服务 */
    SS_FUNC_ID_CLIENT = 3  /* 只调用不接收转发请求的客户端 */
};

/**
 * @brief 搜索结果业务码
 */
enum tagSearchCode {
    SS_SEARCH_CODE_OK = 0,        /* 成功 */
    SS_SEARCH_CODE_NOT_READY = 1, /* 索引未就绪 */
    SS_SEARCH_CODE_BUSY = 2       /* 索引重建中 */
};

/**
 * @brief 搜索请求
 */
struct tagSearchQuery {
    std::string Keyword;   /* 搜索关键词 */
    int64_t CategoryId;    /* 分类 ID */
    int64_t LabelId;       /* 标签 ID */
    int64_t State;         /* 文章状态 */
    int64_t Channel;       /* 频道 */
    int64_t UserId;        /* 作者 ID */
    std::string YearMonth; /* 发布时间年月 */
    int32_t Page;          /* 页码 */
    int32_t PageSize;      /* 每页数量 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagSearchQuery> {
    static void write(ByteArray::ptr ba, const tagSearchQuery& u)
    {
        ba->writeStringVint(u.Keyword);
        ba->writeFint64(u.CategoryId);
        ba->writeFint64(u.LabelId);
        ba->writeFint64(u.State);
        ba->writeFint64(u.Channel);
        ba->writeFint64(u.UserId);
        ba->writeStringVint(u.YearMonth);
        ba->writeFint32(u.Page);
        ba->writeFint32(u.PageSize);
    }

    static void read(ByteArray::ptr ba, tagSearchQuery& u)
    {
        u.Keyword = ba->readStringVint();
        u.CategoryId = ba->readFint64();
        u.LabelId = ba->readFint64();
        u.State = ba->readFint64();
        u.Channel = ba->readFint64();
        u.UserId = ba->readFint64();
        u.YearMonth = ba->readStringVint();
        u.Page = ba->readFint32();
        u.PageSize = ba->readFint32();
    }
};

/**
 * @brief 搜索响应
 */
struct tagSearchResult {
    int32_t Code;              /* 业务码 */
    int64_t Total;             /* 命中总数 */
    std::vector<uint64_t> Ids; /* 当前页文章 ID */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagSearchResult> {
    static void write(ByteArray::ptr ba, const tagSearchResult& u)
    {
        ba->writeFint32(u.Code);
        ba->writeFint64(u.Total);
        chen::rpc::Serializer::Write(ba, u.Ids);
    }

    static void read(ByteArray::ptr ba, tagSearchResult& u)
    {
        u.Code = ba->readFint32();
        u.Total = ba->readFint64();
        chen::rpc::Serializer::Read(ba, u.Ids);
    }
};

/**
 * @brief 搜索服务健康状态
 */
struct tagSearchHealth {
    int32_t Ready;     /* 是否就绪 */
    int64_t Docs;      /* 索引文档数 */
    int64_t BuildTime; /* 最近一次构建耗时（秒） */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagSearchHealth> {
    static void write(ByteArray::ptr ba, const tagSearchHealth& u)
    {
        ba->writeFint32(u.Ready);
        ba->writeFint64(u.Docs);
        ba->writeFint64(u.BuildTime);
    }

    static void read(ByteArray::ptr ba, tagSearchHealth& u)
    {
        u.Ready = ba->readFint32();
        u.Docs = ba->readFint64();
        u.BuildTime = ba->readFint64();
    }
};

#endif // __PROTOCOL_SEARCH_H__
