# Table schema: (group_id:integer, user_id:integer)
class Membership < ActiveRecord::Base
  belongs_to :group
  belongs_to :user
end
