/**
 * @brief 平台服务对外 RPC 协议定义
 * @note 平台服务对外 RPC 协议定义
 */
#ifndef __PROTOCOL_PLATFORM_H__
#define __PROTOCOL_PLATFORM_H__

#include <chen/rpc/serializer.h>
#include <cstdint>
#include <string>

#define PLATFORM_CMD_PING                  2000 /* 连通性自检，返回 func_id */
#define PLATFORM_CMD_GET_SETTINGS          2001 /* 获取系统设置快照 */
#define PLATFORM_CMD_KICK_DEVICE           2002 /* 踢下线指定设备（单向通知） */
#define PLATFORM_CMD_PUSH_EVENT            2003 /* 推送业务事件到 WebSocket（单向通知） */
#define PLATFORM_CMD_LIST_USER_ORGS        2004 /* 获取用户所属组织列表 */
#define PLATFORM_CMD_LIST_USER_ASSIGNMENTS 2005 /* 获取用户可见作业列表 */

/**
 * @brief 系统设置快照
 */
struct tagSystemSettings {
    std::string SiteName;             /* 站点名称 */
    std::string SiteDescription;      /* 站点描述 */
    std::string SiteKeywords;         /* 站点关键词 */
    std::string SiteLogo;             /* 站点 Logo */
    std::string SiteIcon;             /* 站点图标 */
    std::string Favicon;              /* favicon 地址 */
    std::string Language;             /* 默认语言 */
    std::string Timezone;             /* 时区 */
    int32_t EnableRegistration;       /* 是否开放注册 */
    int32_t RequireEmailVerification; /* 是否要求邮箱验证 */
    int32_t AllowComments;            /* 是否允许评论 */
    int32_t ModerateComments;         /* 评论是否需审核 */
    int32_t MaintenanceMode;          /* 维护模式开关 */
    int32_t SessionTimeout;           /* 会话超时（秒） */
    int32_t MaxFileSize;              /* 上传大小上限（MB） */
    std::string AllowedFileTypes;     /* 允许上传的文件类型 */
    std::string SmtpHost;             /* SMTP 主机 */
    int32_t SmtpPort;                 /* SMTP 端口 */
    std::string SmtpUsername;         /* SMTP 用户名 */
    std::string SmtpPassword;         /* SMTP 密码 */
    std::string SmtpEncryption;       /* SMTP 加密方式 */
    std::string FromEmail;            /* 发件邮箱 */
    std::string FromName;             /* 发件人名称 */
    std::string ReplyTo;              /* 回复地址 */
    std::string AdminEmail;           /* 管理员邮箱 */
    std::string BackupSchedule;       /* 备份计划 */
    int64_t UpdatedAt;                /* 更新时间（秒），用于缓存失效 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagSystemSettings> {
    static void write(ByteArray::ptr ba, const tagSystemSettings& u)
    {
        ba->writeStringVint(u.SiteName);
        ba->writeStringVint(u.SiteDescription);
        ba->writeStringVint(u.SiteKeywords);
        ba->writeStringVint(u.SiteLogo);
        ba->writeStringVint(u.SiteIcon);
        ba->writeStringVint(u.Favicon);
        ba->writeStringVint(u.Language);
        ba->writeStringVint(u.Timezone);
        ba->writeFint32(u.EnableRegistration);
        ba->writeFint32(u.RequireEmailVerification);
        ba->writeFint32(u.AllowComments);
        ba->writeFint32(u.ModerateComments);
        ba->writeFint32(u.MaintenanceMode);
        ba->writeFint32(u.SessionTimeout);
        ba->writeFint32(u.MaxFileSize);
        ba->writeStringVint(u.AllowedFileTypes);
        ba->writeStringVint(u.SmtpHost);
        ba->writeFint32(u.SmtpPort);
        ba->writeStringVint(u.SmtpUsername);
        ba->writeStringVint(u.SmtpPassword);
        ba->writeStringVint(u.SmtpEncryption);
        ba->writeStringVint(u.FromEmail);
        ba->writeStringVint(u.FromName);
        ba->writeStringVint(u.ReplyTo);
        ba->writeStringVint(u.AdminEmail);
        ba->writeStringVint(u.BackupSchedule);
        ba->writeFint64(u.UpdatedAt);
    }

    static void read(ByteArray::ptr ba, tagSystemSettings& u)
    {
        u.SiteName = ba->readStringVint();
        u.SiteDescription = ba->readStringVint();
        u.SiteKeywords = ba->readStringVint();
        u.SiteLogo = ba->readStringVint();
        u.SiteIcon = ba->readStringVint();
        u.Favicon = ba->readStringVint();
        u.Language = ba->readStringVint();
        u.Timezone = ba->readStringVint();
        u.EnableRegistration = ba->readFint32();
        u.RequireEmailVerification = ba->readFint32();
        u.AllowComments = ba->readFint32();
        u.ModerateComments = ba->readFint32();
        u.MaintenanceMode = ba->readFint32();
        u.SessionTimeout = ba->readFint32();
        u.MaxFileSize = ba->readFint32();
        u.AllowedFileTypes = ba->readStringVint();
        u.SmtpHost = ba->readStringVint();
        u.SmtpPort = ba->readFint32();
        u.SmtpUsername = ba->readStringVint();
        u.SmtpPassword = ba->readStringVint();
        u.SmtpEncryption = ba->readStringVint();
        u.FromEmail = ba->readStringVint();
        u.FromName = ba->readStringVint();
        u.ReplyTo = ba->readStringVint();
        u.AdminEmail = ba->readStringVint();
        u.BackupSchedule = ba->readStringVint();
        u.UpdatedAt = ba->readFint64();
    }
};

/**
 * @brief 用户所属组织简介
 */
struct tagUserOrgBrief {
    int64_t OrgId;              /* 组织 id */
    std::string OrgName;        /* 组织名称 */
    std::string OrgDescription; /* 组织描述 */
    std::string Type;           /* 组织类型 */
    int32_t Role;               /* 用户在该组织中的角色 */
    int64_t JoinTime;           /* 加入时间（秒） */
    int64_t MemberCount;        /* 成员数 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagUserOrgBrief> {
    static void write(ByteArray::ptr ba, const tagUserOrgBrief& u)
    {
        ba->writeFint64(u.OrgId);
        ba->writeStringVint(u.OrgName);
        ba->writeStringVint(u.OrgDescription);
        ba->writeStringVint(u.Type);
        ba->writeFint32(u.Role);
        ba->writeFint64(u.JoinTime);
        ba->writeFint64(u.MemberCount);
    }

    static void read(ByteArray::ptr ba, tagUserOrgBrief& u)
    {
        u.OrgId = ba->readFint64();
        u.OrgName = ba->readStringVint();
        u.OrgDescription = ba->readStringVint();
        u.Type = ba->readStringVint();
        u.Role = ba->readFint32();
        u.JoinTime = ba->readFint64();
        u.MemberCount = ba->readFint64();
    }
};

/**
 * @brief 用户可见作业简介
 */
struct tagUserAssignmentBrief {
    int64_t Id;              /* 作业 id */
    std::string Name;        /* 作业名称 */
    std::string SubjectName; /* 科目名称 */
    int64_t Deadline;        /* 截止时间（秒） */
    int32_t Status;          /* 状态：见 AssignmentManager::Status */
    int32_t Priority;        /* 优先级 */
    int64_t CreateTime;      /* 创建时间（秒） */
    std::string Description; /* 作业描述 */
    std::string FileType;    /* 允许的提交文件类型 */
    int32_t MaxSize;         /* 提交文件大小上限 */
};

/**
 * @brief RPC序列化适配器 - 自动生成
 */
template <>
struct chen::rpc::Serialization<tagUserAssignmentBrief> {
    static void write(ByteArray::ptr ba, const tagUserAssignmentBrief& u)
    {
        ba->writeFint64(u.Id);
        ba->writeStringVint(u.Name);
        ba->writeStringVint(u.SubjectName);
        ba->writeFint64(u.Deadline);
        ba->writeFint32(u.Status);
        ba->writeFint32(u.Priority);
        ba->writeFint64(u.CreateTime);
        ba->writeStringVint(u.Description);
        ba->writeStringVint(u.FileType);
        ba->writeFint32(u.MaxSize);
    }

    static void read(ByteArray::ptr ba, tagUserAssignmentBrief& u)
    {
        u.Id = ba->readFint64();
        u.Name = ba->readStringVint();
        u.SubjectName = ba->readStringVint();
        u.Deadline = ba->readFint64();
        u.Status = ba->readFint32();
        u.Priority = ba->readFint32();
        u.CreateTime = ba->readFint64();
        u.Description = ba->readStringVint();
        u.FileType = ba->readStringVint();
        u.MaxSize = ba->readFint32();
    }
};

#endif // __PROTOCOL_PLATFORM_H__
