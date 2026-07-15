/**
 * @brief github相关服务的RPC协议定义
 * @note github相关服务的RPC协议定义
 */
#ifndef __PROTOCOL_SS_GITHUB_H__
#define __PROTOCOL_SS_GITHUB_H__

#include <chen/rpc/serializer.h>
#include <cstdint>
#include <string>

/**
 * @brief GitHub Pull Request 事件数据（对应 pull_request webhook）
 */
struct tagGithubPRInfo {
    std::string Action;     /* 事件类型: opened/closed/reopened/synchronize/edited/labeled/unlabeled */
    int32_t Number;         /* PR 编号 */
    std::string Title;      /* PR 标题 */
    std::string Body;       /* PR 描述/正文 */
    std::string State;      /* 状态: open/closed */
    std::string Author;     /* 作者 GitHub 用户名 */
    std::string HeadBranch; /* 源分支 */
    std::string BaseBranch; /* 目标分支 */
    std::string HeadSha;    /* 最新 commit SHA */
    bool Merged;            /* 是否已合并 */
    int32_t ChangedFiles;   /* 变更文件数 */
    int32_t Additions;      /* 新增行数 */
    int32_t Deletions;      /* 删除行数 */
    std::string CreatedAt;  /* 创建时间 */
    std::string ClosedAt;   /* 关闭时间 */
    std::string MergedAt;   /* 合并时间 */
    std::string RepoOwner;  /* 仓库所有者 */
    std::string RepoName;   /* 仓库名称 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagGithubPRInfo> {
    static void write(ByteArray::ptr ba, const tagGithubPRInfo& u) {
        ba->writeStringVint(u.Action);
        ba->writeFint32(u.Number);
        ba->writeStringVint(u.Title);
        ba->writeStringVint(u.Body);
        ba->writeStringVint(u.State);
        ba->writeStringVint(u.Author);
        ba->writeStringVint(u.HeadBranch);
        ba->writeStringVint(u.BaseBranch);
        ba->writeStringVint(u.HeadSha);
        ba->writeFint8(u.Merged ? 1 : 0);
        ba->writeFint32(u.ChangedFiles);
        ba->writeFint32(u.Additions);
        ba->writeFint32(u.Deletions);
        ba->writeStringVint(u.CreatedAt);
        ba->writeStringVint(u.ClosedAt);
        ba->writeStringVint(u.MergedAt);
        ba->writeStringVint(u.RepoOwner);
        ba->writeStringVint(u.RepoName);
    }

    static void read(ByteArray::ptr ba, tagGithubPRInfo& u) {
        u.Action = ba->readStringVint();
        u.Number = ba->readFint32();
        u.Title = ba->readStringVint();
        u.Body = ba->readStringVint();
        u.State = ba->readStringVint();
        u.Author = ba->readStringVint();
        u.HeadBranch = ba->readStringVint();
        u.BaseBranch = ba->readStringVint();
        u.HeadSha = ba->readStringVint();
        u.Merged = ba->readFint8() != 0;
        u.ChangedFiles = ba->readFint32();
        u.Additions = ba->readFint32();
        u.Deletions = ba->readFint32();
        u.CreatedAt = ba->readStringVint();
        u.ClosedAt = ba->readStringVint();
        u.MergedAt = ba->readStringVint();
        u.RepoOwner = ba->readStringVint();
        u.RepoName = ba->readStringVint();
    }
};

/**
 * @brief GitHub PR Review 事件数据（对应 pull_request_review webhook）
 */
struct tagGithubPRReviewInfo {
    std::string Action;      /* 事件类型: submitted/edited/dismissed */
    int32_t PRNumber;        /* PR 编号 */
    std::string Reviewer;    /* 审查者 GitHub 用户名 */
    std::string State;       /* 审查结果: approved/changes_requested/commented/dismissed */
    std::string SubmittedAt; /* 审查提交时间 (ISO8601) */
    std::string RepoOwner;   /* 仓库所有者 */
    std::string RepoName;    /* 仓库名称 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagGithubPRReviewInfo> {
    static void write(ByteArray::ptr ba, const tagGithubPRReviewInfo& u) {
        ba->writeStringVint(u.Action);
        ba->writeFint32(u.PRNumber);
        ba->writeStringVint(u.Reviewer);
        ba->writeStringVint(u.State);
        ba->writeStringVint(u.SubmittedAt);
        ba->writeStringVint(u.RepoOwner);
        ba->writeStringVint(u.RepoName);
    }

    static void read(ByteArray::ptr ba, tagGithubPRReviewInfo& u) {
        u.Action = ba->readStringVint();
        u.PRNumber = ba->readFint32();
        u.Reviewer = ba->readStringVint();
        u.State = ba->readStringVint();
        u.SubmittedAt = ba->readStringVint();
        u.RepoOwner = ba->readStringVint();
        u.RepoName = ba->readStringVint();
    }
};

/**
 * @brief GitHub RPC 错误码定义
 */
enum tagGithubError {
    GITHUB_REPO_NOT_FOUND = 1,       /* GitHub RPC 错误码: 仓库未找到 */
    GITHUB_PR_NOT_FOUND = 2,         /* GitHub RPC 错误码: PR 未找到 */
    GITHUB_DB_CONNECTION_FAILED = 3, /* GitHub RPC 错误码: 数据库连接失败 */
    GITHUB_DB_OPERATION_FAILED = 4,  /* GitHub RPC 错误码: 数据库操作失败 */
    GITHUB_UNKNOWN_ERROR = 5         /* GitHub RPC 错误码: 未知错误 */
};

#endif // __PROTOCOL_SS_GITHUB_H__
